#include "CUSTOM_FUNCTIONS_HEADER.h"


//NOTE NOT MY FUNCTION
//FUNCTION MADE BY JONATHAN S HARBOUR

void drawframe(BITMAP *dest, BITMAP *source, int x, int y, int width, int height, int startx, int starty, int columns, int frame, bool transparency){

    //calculate frame position

    int framex = startx + (frame % columns) * width;
    int framey = starty + (frame / columns) * height;

    //blit to source
    if(transparency)
        masked_blit(source, dest, framex, framey, x, y, width, height);
    else
        blit(source, dest, framex, framey, x, y, width, height);


}

//Obtain directory of current game without game file name.exe

string dir_of_game(){

    string filename = ""; //Full File name
    string filepathstr = ""; //Filepath string
    string newpath = ""; //Directory of file path
    char pathtofile[MAX_PATH];

    HMODULE GetModH = GetModuleHandle(NULL);

    //GET PATH OF SERVER.EXE
    GetModuleFileName(GetModH,pathtofile,sizeof(pathtofile));

    filepathstr.append(pathtofile); //insert char pathtofile into string container filepathstr
    filename.append(PathFindFileNameA(pathtofile)); //Get file name

    std::size_t strsize = filepathstr.find(filename); //Process
    if (strsize!=std::string::npos)
        newpath = filepathstr.substr(0, strsize);

    return newpath;

}

vector<string> Return_List_OG_LEVELS(bool relative_directory){



    string searchpath = dir_of_game();
    string tempstr = "";
    searchpath.append("OG_LEVELS\\*");

    vector<string> Level_File_Name;


    WIN32_FIND_DATA file;
    HANDLE filefound = NULL;

    filefound = FindFirstFile(searchpath.c_str(), &file);

    while(FindNextFile(filefound, &file)){

        if(relative_directory){
            tempstr.append("OG_LEVELS\\");
        }
        tempstr.append(file.cFileName);

        Level_File_Name.push_back(tempstr);

        tempstr.clear();

    }

    return Level_File_Name;
}

int if_neg_ret_zero(int num){

    return (num < 0) ? 0 : num;

}

vector<string> parse_out_file_extension(vector<string> strlist){

    string::iterator it;

    for(int i = 0; i < strlist.size(); i++){

        for ( it = strlist[i].begin() ; it < strlist[i].end(); it++ ){

                if (*it == '.'){
                    while(it < strlist[i].end()){
                        strlist[i].erase(it);
                        it--;
                        it++;
                    }
                }
        }
    }
    return strlist;
}

vector<Game_Level> Load_Level_List(vector<string> LEVEL_LIST){

    vector<Game_Level> Levels;
    Game_Level lvl;
    ifstream instream;

    for(int i = 0; i<LEVEL_LIST.size(); i++){

        instream.open(LEVEL_LIST[i].c_str());
        string line, op_code = "";
        int op_int;

        int it = 0;
        if(instream.is_open()){

            while( instream.good()){

                getline(instream, line);

                for(it = 0; it < line.size(); it++){

                    if(line[it] == '*'){
                        it++;

                        while(line[it] != '*'){
                            op_code.push_back(line[it]);
                            it++;
                    }

                        op_int = atoi(op_code.c_str());
                        op_code.clear();

                        switch(op_int){
                            case 1001: lvl.setFile_Name(line.substr(it+1, line.size()));
                                break;
                            case 1002: lvl.setLevel_Name(line.substr(it+1, line.size()));
                                break;
                            case 1003: lvl.setGraphic_File_Name(line.substr(it+1, line.size()));
                                break;
                        }

                    }

                }

                }
                Levels.push_back(lvl);
            }
            instream.close();
            instream.clear();
        }

        return Levels;
}

vector<string> Ret_Level_List_Name_Game_Info(vector<Game_Level>Level_Info){

    string tempstr;
    vector<string> disp_str_arr;

    for (int i = 0; i < Level_Info.size(); i++){
        tempstr = Level_Info[i].getLevel_Name();
        disp_str_arr.push_back(tempstr);
    }

    return disp_str_arr;
}
