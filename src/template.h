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

#include <httppp/http.h>
#include <httppp/httpd.h>

#ifndef TEMPLATE_H
#define TEMPLATE_H

namespace tinyblog {
  class TemplateVar {
  public:
      
      /*SetData to Template*/
      void setData();
      const char *getData();
      
  private:
      char  *_Name;
      char  *_Data;
      size_t _DataSize;
  };
    
  class TemplateStatic {
      
  };
  
  class TemplateNode{
  public:
      
  private:
      TemplateNode();
      ~TemplateNode();
      TemplateStatic  *_StaticData;   
      TemplateVar     *_VarData;
      TemplateNode    *_nextTemplateNode;
  };
  
  class Template {
  public:
      Template *nextTemplate();
  private:
      Template();
      ~Template();
      char          _Name[MAX_TEMPLATE_NAMESIZE];
      TemplateNode *_firstTemplateNode;
      TemplateNode *_lastTemplateNode;
      Template     *_nextTemplate;
      friend class TemplatePool;
  };
  
  class TemplatePool {
  public:
      static TemplatePool& Instance();
      ~TemplatePool();
      
      bool getTemplateCopy(const char *name,Template **cpytemplate);
      /*Set template options*/
      void setTemplatePath(const char *path);
      void clearPool();
      
  private:
      TemplatePool();
      char     *_TemplatePath;
      Template *_firstTemplate;
      Template *_lasteTemplate;
      TemplatePool( const TemplatePool& );
      TemplatePool & operator = (const TemplatePool &);
  };
  
};

#endif
