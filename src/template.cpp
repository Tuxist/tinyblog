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

#include "template.h"

/*Template*/

tinyblog::Template::Template(){
  _firstTemplateNode=NULL;
  _lastTemplateNode=NULL;
  _nextTemplate=NULL;
}

tinyblog::Template::~Template(){
}

tinyblog::Template *tinyblog::Template::nextTemplate(){
  return _nextTemplate;
}

/*Template Pool*/
tinyblog::TemplatePool::TemplatePool(){
  _TemplatePath=NULL;
}

tinyblog::TemplatePool::TemplatePool(const tinyblog::TemplatePool&){
  _TemplatePath=NULL;
}

tinyblog::TemplatePool::~TemplatePool(){

}

void tinyblog::TemplatePool::setTemplatePath(const char* path){

    
}

void tinyblog::TemplatePool::clearPool(){
    delete[] _TemplatePath;
    _TemplatePath=NULL;
    delete _firstTemplate;
    _firstTemplate=NULL;
    _lasteTemplate=NULL;
}


tinyblog::TemplatePool & tinyblog::TemplatePool::Instance(){
  static TemplatePool _Instance;
  return _Instance;
}


bool tinyblog::TemplatePool::getTemplateCopy(const char* name, tinyblog::Template **cpytemplate){
    for(Template *curtpl=_firstTemplate; curtpl; curtpl=curtpl->nextTemplate()){
        
    }
}

