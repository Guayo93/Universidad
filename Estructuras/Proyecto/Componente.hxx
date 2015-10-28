#ifndef __COMPONENTE__HXX__
#define __COMPONENTE__HXX__
// -----------------------------------------------------------------------
Componente::
Componente(){
};

// -------------------------------------------------------------------------
Componente::
~Componente( )
{
}

// load-------------------------------------------------------------------
ObjectView* Componente::
load (std::string archivo)
{
  this->obj = new ObjectView( );

  std::ifstream fe ( archivo.c_str() );
  std::stringstream lect;
  std::list<std::string> ar;
  std::string line, num, nam;
  std::list<std::string>::iterator it;
  std::string::iterator it2, aux;
  std::list<float>::iterator itD;

  if(fe)
  {
    fe.seekg( 0, fe.end );
    unsigned long file_length = fe.tellg( );
    fe.seekg( 0, fe.beg );
	char* file_buffer = new char[ file_length ];
	fe.read( file_buffer, file_length );
	fe.close();
	
	std::istringstream file( file_buffer );
	do
    {
      std::getline( file, line );
      ar.push_back(line);
      
    }while(file);
    it = ar.begin();

    if(ar.begin() == ar.end()) std::cout<< archivo << "does not contain any object." <<std::endl; 

    nam = *it; it++; 
    this->name = nam;
    float  nn;
    std::stringstream ss(*it); int n, i=0, j; ss >> n; it++;
    
    std::list<float> cords; 
    this->nCant = n;
    n= n*3;
    while(*it != "-1")
    {
      
      if(cords.size() == 0)
      {
        while(cords.size() != n)
        {
          line = *it;
          it2 = line.begin();

          while(it2 != line.end() && cords.size() != n)
          {

            aux = it2;
            if(it2 != line.end())aux++;
            if(*it2 != ' ')
            {
              num+=*it2;
            }
            if(*it2 == ' ' )
            {
              std::stringstream s(num); s>>nn; cords.push_back(nn);//std::cout<<cords.back(); 
              num= "";
            }
            if(aux == line.end() && *it2 != ' ')
            {
              num+=*aux;
              std::stringstream s(num); s>>nn; cords.push_back(nn);//std::cout<<cords.back();
              num= "";
              
            }
            
            if(it2 != line.end())it2++;
          }
//std::cout<<std::endl;
          it++;
        }
        if(cords.size() % 3 == 0)
        {
		    itD = cords.begin();
		    while( itD != cords.end() )
		      {
		        float cx,cy,cz;
		        cx = *itD; if(itD != cords.end())itD++;
		        cy = *itD; if(itD != cords.end())itD++;
		        cz = *itD; if(itD != cords.end())itD++;
		        
		        this->obj->AddVertex( cx, cy, cz );
		      }
		      cords.push_back(1);
        }
      }
      else
      {
        if(*it != "-1")
        {
          line = *it;
          it2 = line.begin();
          num+=*it2;
          std::stringstream s(num); s>>nn;float k=nn; 
          j=0; num="";
          int cord[] = { 0, 0, 0, 0, 0, 0, 0};
          //std::cout<<"-"<<std::endl;
          while( j!=(k+1) )
          {

            aux = it2;
            if(it2 != line.end())aux++;
            if(*it2 != ' ')
            {
              num+=*it2;
            }
            if(*it2 == ' ')
            { 
              std::stringstream s(num); s>>nn; cord[j]=nn;
              num="";
              j++;
            }
            if(aux == line.end() && *it2 != ' ')
            {
              num+=*aux;
              std::stringstream s(num); s>>nn; cord[j]=nn;
              num= "";
              j++;
            }
            if(it2 != line.end()) it2++;
          }
          
          //this->obj->AddCell( k, cord );
          if(cord[0] == 3){this->obj->AddCell(k, cord[1], cord[2], cord[3] );}
          if(cord[0] == 4){this->obj->AddCell(k, cord[1], cord[2], cord[3], cord[4]);}
          if(cord[0] == 6){this->obj->AddCell(k, cord[1], cord[2], cord[3], cord[4], cord[5], cord[6]);}
          //for(int i=0; i < this->obj->m_Indices.size(); i++) std::cout<<this->obj->m_Indices[i]<<std::endl;
            
        }
          
        if(it != ar.end()) it++;
      }
    }
   std::cout<<"Object "<< nam << " successfuly loaded from "<< archivo << "." <<std::endl; 
  }
  else
  {
    std::cout<<"Could not open file "<< archivo<< "." <<std::endl;
  }
  return this->obj;
};

// -------------------------------------------------------------------------

#endif
