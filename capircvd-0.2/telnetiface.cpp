#include<iostream>
#include<fstream>
#include<strstream>
#include<string>
#include<stdio.h>
#include<map>
#include<iterator>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iomanip.h>
#include"ccconf.h"
#include"tools.h"

// socket and telnet-stuff...

int response(fstream &f,string aus,string &ein)
 {
 char line[1024];
 char c;
 f << aus << flush;
 f.getline(line,1024);
 ein=line;
 ein=ein.substr(0,ein.find(13));
 if(dbg_telnet)
  cdebug << " rcvd cmdline: \"" << ein << "\"" << endl;
 }

void* telnetserver_func(void *a) 
 {
 int fd=*((int*)a);
 fstream f(fd);
 f.exceptions(0);
 string username,password,cmd,sektion;
 int i;
 char c;

 if(dbg_telnet) 
  cdebug << "new telnetsession:" << fd << endl;

 response(f,"please login  :",username);
 response(f,string("your password :"),password);

 if(dbg_telnet)
  cdebug << "U:" << username << " P:" << password << endl;

 bool x=false,root=false;

 map <string,map<string,string> > *conf=&(cConf->conf);

 if(conf->find("passwd")!=conf->end() && (*conf)["passwd"].find(username.c_str())!=(*conf)["passwd"].end() && (*conf)["passwd"][username.c_str()]!="disabled")
  x=(*conf)["passwd"][username.c_str()]==password;

 if(username=="root" && conf->find("admin")!=conf->end() && (*conf)["admin"].find("password")!=(*conf)["admin"].end() && (*conf)["admin"]["password"]==password)
  {
  x=root=true;
  }

 if(x)
  {
  f << "login successful..." << (char)10 << (char)13;
  f << "   try 'help' if you don't know what to do ;-) ..." << (char)10 << (char)10 << (char)13;
  }
 else
  {
  f << "login unsuccessful!!!" << (char)10 << (char)13 << (char)10;
  f.close();
  return NULL;
  }

 string cmds[]={"exit","quit","logout","ls","cd","passwd","shutdown","set","help","save","dump","del"};

 while(cmd!="exit" && cmd!="quit" && cmd!="logout" && f.good())
  {
  string cmdline;
  response(f,string("/")+sektion+(root?" # ":" : "),cmdline);
  int dummy3;
  while( (dummy3=cmdline.find(string("  "))) >= 0 )
   {
   cmdline=cmdline.substr(0,dummy3)+cmdline.substr(dummy3+2);
   }
  cmd=cmdline.substr(0,cmdline.find(string(" ")));
  int i=0;
  for(;i<12 && cmds[i]!=cmd ;i++);
  switch(i)
   {
   case 0:
   case 1:
   case 2:
     f << "logout..." << (char)10 << (char)13;
    break;
   case 3:
     {
     if(sektion=="")
      {
      f << "existing sections:" << (char)10 << (char)10 << (char)13;
      map<string,map<string,string> >::iterator i=(*conf).begin();
      for(;i!=(*conf).end();i++)
       {
       if(root || ( (*conf)[(*i).first].find("user")!=(*conf)[(*i).first].end() && (*conf)[(*i).first]["user"]==username) )
        f << "   *   " << (*i).first << (char)10 << (char)13;
       else
        f << "noauth " << (*i).first << (char)10 << (char)13;
       }
      f << (char)10; 
      }
     else
      {
      f << "configuration in section \"" << sektion << "\":" << (char)10 << (char)10 << (char)13;
//      f << "=" << sektion << (char)10 << (char)13;
      map<string,string>::iterator i=(*conf)[sektion.c_str()].begin();
      for(;i!=(*conf)[sektion.c_str()].end();i++)
       {
       f << (*i).first << setw(40-(*i).first.length()) << " " << setw(0) << (*i).second << (char)10 << (char)13;
       }
      f << (char)10; 
      }
     }
    break;
   case 4:
     {
     string oldsektion=sektion,answer;
     if(cmdline.find(" ")<=0 || cmdline.find(" ")>cmdline.length())
      {
      f << "Hey, forgot something ???" << (char)10 << (char)13;
      break;
      } 
     sektion=cmdline.substr(cmdline.find(" ")+1);
     if(sektion=="/" || sektion=="..")
      {
      f << "changing to section \"" << sektion << "\"..." << (char)10 << (char)13;
      sektion="";
      break;
      }
     if(conf->find(sektion.c_str())==conf->end())
      {
      response(f,string("section '")+sektion+"' does not exist! to create answer 'y':",answer);
      if(answer=="y")
       {
       break;
       }
      sektion=oldsektion;
      }
     else
      {
      if(root || ( (*conf)[sektion.c_str()].find("user")!=(*conf)[sektion.c_str()].end() && (*conf)[sektion.c_str()]["user"]==username))
       f << "changing to section \"" << sektion << "\"..." << (char)10 << (char)13;
      else
       {
       f << "you are not allowed to use section \"" << sektion << "\" ! using section \"/\"" << (char)10 << (char)13;
       sektion="";
       }
      }
     }
    break;
   case 5:
     if(root)
      {
      (*conf)["admin"]["password"]=cmdline.substr(cmdline.find(" ")+1);
      f << "changed password for \"" << username << "\" to \"" << (*conf)["admin"]["password"] << "\"" << (char)10 << (char)10 << (char)13;
      }
     else
      {
      (*conf)["passwd"][username.c_str()]=cmdline.substr(cmdline.find(" ")+1);
      f << "changed password for \"" << username << "\" to \"" << (*conf)["passwd"][username.c_str()] << "\"" << (char)10 << (char)10 << (char)13;
      }
    break;
   case 6:
     if(root)
      throw(string("shutting down capircvd"));
    break;
   case 7:
     {
     if(sektion=="")
      {
      f << "section \"/\" can`t contain options, change to a real section..." << (char)10 << (char)10 << (char)13;
      break;
      }
     if(cmdline.find(" ")<0 || cmdline.find(" ")>cmdline.length())
      {
      f << "Hey, forgot something ???" << (char)10 << (char)13;
      break;
      }
     string value,option=cmdline.substr(cmdline.find(" ")+1);
     if(option.find(" ")>0 && option.find(" ")<option.length())
      {
      value=option.substr(option.find(" ")+1);
      option=option.substr(0,option.find(" "));
      }
     else
      response(f,string("setting \"")+cmdline.substr(cmdline.find(" ")+1)+"\" to value:",value);
     (*conf)[sektion.c_str()][option]=value;
     }
    break;
   case 8:
     f << "you can use following commands, some only as 'root'" << (char)10 << (char)13;
     f << "" << (char)10 << (char)13;
     f << "exit | quit | logout     to exit your telnet-session" << (char)10 << (char)13;
     f << "ls                       to show configurationoptions" << (char)10 << (char)13 <<
          "                         in the current section or available" << (char)10 << (char)13 <<
          "                         sections if you are in '/' " << (char)10 << (char)13;
     f << "cd SECTION               to change the current section " << (char)10 << (char)13;
     f << "                         if SECTION does not exist it asks to" << (char)10 << (char)13;
     f << "                         create it..." << (char)10 << (char)13;
     f << "del OPTION/SECTION       If working in '/' you can delete a section," << (char)10 << (char)13;
     f << "                         if inside a section you can delete an" << (char)10 << (char)13;
     f << "                         an option. You will be asked to confirm" << (char)10 << (char)13;
     f << "passwd PASSWORD          to change the own password" << (char)10 << (char)13;
     f << "shutdown                 terminates capircvd, only as root !" << (char)10 << (char)13;
     f << "set OPTION               for changing the option, you are asked for" << (char)10 << (char)13 <<
          "                         a new value!" << (char)10 << (char)13;
     f << "dump                     dumps the config to session," << (char)10 << (char)13 << 
          "                         see README" << (char)10 << (char)13;
     f << "save                     dumps the config to capircvd.state," << (char)10 << (char)13 << 
          "                         see README" << (char)10 << (char)13;
     f << "for more help see README or contact alex@brickwedde.de ..." << (char)10 << (char)10 << (char)13;
    break;
   case 9:
     if(root)
      if(cConf==NULL || ! cConf->dumpconf(configdir+"/capircvd.state"))
       f << "dump failed !!! " << (char)10 << (char)10 << (char)13;
      else
       f << "created capircvd.state !!! " << (char)10 << (char)10 << (char)13;
    break;
   case 10:
     { 
     f << "# dump of capircvd-configuration " << (char)10 << (char)13;
     map<string,map<string,string> >::iterator ii=conf->begin();
     for(;ii!=conf->end();ii++)
      {
      f << (char)10 << (char)13 << "=" << (*ii).first << (char)10 << (char)13;
      map<string,string>::iterator i=(*ii).second.begin();
      for(;i!=(*ii).second.end();i++)
       {
       f << (*i).first <<  setw(40-(*i).first.length()) << " " << setw(0) << (*i).second << (char)10 << (char)13;
       }
      }
     f << "# end of dump" << (char)10 << (char)13;
     }
    break;
   case 11:
     {
     string what=cmdline.substr(cmdline.find(" ")+1),answer;
     if(sektion=="")
      {
      response(f,string("erase section '")+what+"' ? Answer 'y' to do so:",answer);
      if(answer=="y")
       {
       conf->erase(what);
       f << "erased section '" << what << "'" << (char)10 << (char)13;
       }
      else
       f << "calm down, nothing happened..." << (char)10 << (char)13;
      }
     else
      {
      response(f,string("erase option '")+what+"' ? Answer 'y' to do so:",answer);
      if(answer=="y")
       {
       (*conf)[sektion].erase(what);
       f << "erased option '" << what << "' in section '" << sektion << "'" << (char)10 << (char)13;
       }
      else
       f << "calm down, nothing happened..." << (char)10 << (char)13;
      }
     }
    break;
   }
  }
 f.close();
}

void * acceptthread_func(void * x)
 {
 int sock=*((unsigned int *)x);
 int conn;
 socklen_t addrlen=sizeof(sockaddr_in);
 sockaddr_in caddr;
 while(conn=accept(sock,(struct sockaddr *)&caddr,&addrlen)) 
  {
  pthread_t p;
  pthread_create(&p,NULL,telnetserver_func,&conn);
  }
 }

