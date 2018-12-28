int TableDef::parse_array(string line, string type, int col_count)
{

    //for(int j=0;j<str.length();j++)
    //{ 
    //    printf("array %d:%x\n",j,str.c_str()[j]);
    //} 
    unsigned int start=0;
    unsigned int loc = 0;
    char tab = ':';
    loc = line.find(tab, start );
    start = loc + 1;
    int i=0;
    tab = ',';
    for (;i<col_count;i++)
    {   
        if (i==col_count-1)
            loc = line.length();
        else
            loc = line.find(tab, start );
        if( loc != string::npos )
        {   
            string element = line.substr(start,loc-start);
            //cout <<start<<" "<<loc<<" Found sub string " << sub << endl;

            start = loc + 1;
            while(line.c_str()[loc]==' ')
            {   
                start++;
            }   
            //printf("the type of this word is %s\n",type.c_str() );
            parse_column(type, element);
        }   
        else
        {   
            cout << "Didn't find sub" << endl;
        }   
        cout<<endl;
    }   
}
