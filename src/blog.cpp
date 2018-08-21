/*******************************************************************************
Copyright (c) 2018, Jan Koester jan.koester@gmx.net
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/ 

#include <iostream>
#include <sstream>

#include "blog.h"

void sendResponse(libhttppp::Connection *curcon,libhttppp::HttpRequest *curreq) {
     libhttppp::HttpResponse curres;
     curres.setState(HTTP200);
     curres.setVersion(HTTPVERSION(1.1));
     curres.setContentType("text/html");
     std::stringstream condat;
     condat  << "<!DOCTYPE HTML>"
             << " <html>"
             << "  <head>"
             << "    <title>ConnectionTest</title>"
             << "    <meta content=\"\">"
             << "    <meta charset=\"utf-8\">"
             << "    <style></style>"
             << "  </head>"
             << "<body>";
     for(libhttppp::HttpHeader::HeaderData *preq = curreq->getfirstHeaderData(); preq; preq=curreq->nextHeaderData(preq)){
       condat  << curreq->getKey(preq) 
               << ": "
               << curreq->getValue(preq)
               << "<br/>";
     }
     condat  << "</body></html>";
     std::string buffer=condat.str();
     curres.send(curcon,buffer.c_str(),buffer.length());
};

tinyblog::BlogIndexPage::BlogIndexPage(){
  Template *blogtpl=NULL;
  TemplatePool::Instance().getTemplateCopy("Index.tpl.html",&blogtpl);
    
}

tinyblog::BlogIndexPage::~BlogIndexPage(){
}

tinyblog::BlogController::BlogController(libhttppp::ServerSocket* serversocket) : libhttppp::Event(serversocket){
};
  
tinyblog::BlogController::~BlogController(){
}

void tinyblog::BlogController::RequestEvent(libhttppp::Connection* curcon)
{
   try{
     libhttppp::HttpRequest curreq;
     curreq.parse(curcon);
     const char *url=curreq.getRequestURL();
     if(url){
         if(strcmp("/",url)==0){
             sendResponse(curcon,&curreq);
         }
     }else{
     libhttppp::HttpResponse curres;
     curres.setState(HTTP404);
     curres.setVersion(HTTPVERSION(1.1));
     curres.setContentType("text/html");         
     }
     
   }catch(libhttppp::HTTPException &e){
     std::cerr << e.what() << "\n";
     throw e;
   }
  }

  
tinyblog::Blog::Blog(int argc, char** argv) : HttpD(argc,argv){
  CmdController->registerCmd("templatepath",'t', true,(const char*) NULL,"Templatepath");
  CmdController->registerCmd("dbpath",'d', true,(const char*) NULL,"DBPath");
  CmdController->parseCmd(argc,argv);
  if (!CmdController->checkRequired()) {
    CmdController->printHelp();
    _httpexception.Critical("cmd parser not enough arguments given");
    throw _httpexception;
  }
  if(CmdController->getHTTPDCmdbyKey("templatepath")){
    TemplatePool::Instance().setTemplatePath(CmdController->getHTTPDCmdbyKey("templatepath")->getValue());
  }
}

tinyblog::Blog::~Blog(){
    TemplatePool::Instance().clearPool();
}

void tinyblog::Blog::RunEventLoop(){
  libhttppp::HTTPException httpexception;
  try {
    BlogController blogcontroller(getServerSocket());
    blogcontroller.runEventloop();
  }catch(libhttppp::HTTPException &e){
    std::cerr << e.what() << "\n";
  }    
}


int main(int argc, char** argv){
  tinyblog::Blog blog(argc,argv);
  blog.RunEventLoop();
}
