int TableDef::parse_line(string line, int col_count)
{  

    //for(int j=0;j<str.length();j++)
    //{
    //    printf("array %d:%x\n",j,str.c_str()[j]);
    //}
    if (col_count == 0)
        col_count = getColCount();
    unsigned int start=0;
    unsigned int loc = 0;
    int i=0;
    char tab = ' ';
    for (;i<col_count;i++)
    {  
        if (i==col_count-1)
            loc = line.length();
        else
            loc = line.find(tab, start );
        if( loc != string::npos )
        {     
            string sub = line.substr(start,loc-start);
            //cout <<start<<" "<<loc<<" Found sub string " << sub << endl;
            while(line.c_str()[loc]==' ')
            {  
                loc++;
            } 
            start = loc;
            string type = get_type(i);
            parse_column(type, sub);
            //printf("the type of this word is %s\n",type.c_str() );
            //cout << "Found Omega at " << loc << endl;
        }
        else
        {
            cout << "Didn't find sub" << endl;
        }
        cout<<endl;
    }
}
