#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

int main(){

    int state_forecast=12000; //total state forecast
    
    double region[4];  // for all regions
    region[0]=2800;//east zonal forecast
    region[1]=2000;//west zonal forecast
    region[2]=1500;//north zonal forecast
    region[3]=6500;//south zonal forecast

    double sum_region = region[0]+region[1]+region[2]+region[3];   //sum of all regions forecast
    double diff_region = sum_region-state_forecast;    //difference between total region forecast and total state forecast

    //manipulate the region's value
    for(int i=0;i<4;i++){
        region[i]=region[i]-(region[i]/sum_region)*diff_region;  // for propotainting the region's value according to total region forecast
    }
    
    vector<float>East,West,North,South;   // for regionwise data storing
    
    ifstream fin;      // for input operations on the given input file
    fin.open("input.csv"); 

    vector<string> row;   // for every individual row input
    string line, word;  
    int line_no=0,east=0,west=0,north=0,south=0;  // line_no is for wind farm numbering and east,west,north,south are for regionwise

    while (getline(fin,line)) {  // run the loop till the end of the input data
        row.clear(); //clear the every time to get the new row 
        istringstream s(line);
        
        while (getline(s, word, ',')) {  //run the loop till line is converted into words
            row.push_back(word); 
        }

        string temp = row[0];  // for plant name for ex E1,E2...,W1...N1...S1
        if(temp[0]=='E'){       //if plant name starts with E then put the value in East vector
            east++;
            East.push_back(stof(row[1]));  //stof for changing the string to float
        }
        if(temp[0]=='W'){
            west++;
            West.push_back(stof(row[1]));
        }
        if(temp[0]=='N'){
            north++;
            North.push_back(stof(row[1]));
        }
        if(temp[0]=='S'){
            south++;
            South.push_back(stof(row[1]));
        }

        line_no++;  //increment the line number to get the next entry
        
    } 

    //for manuplating the individual regions
    // "it" is used as iterator
    float east_sum = 0;
    for(auto it:East){
        east_sum+=it;
    }

    float east_diff = east_sum-region[0];
    
    float new_east = 0;
    for(auto &it:East){
        it = it-(it/east_sum)*east_diff;
        new_east+=it;  // the new total east zone forecast value
    }

    float west_sum = 0;
    for(auto it:West){
        west_sum+=it;
    }

    float west_diff = west_sum-region[1];
    
    float new_west = 0;
    for(auto &it:West){
        it = it-(it/west_sum)*west_diff;
        new_west+=it;
    }
   
    float north_sum = 0;
    for(auto it:North){
        north_sum+=it;
    }

    float north_diff = north_sum-region[2];
    
    float new_north = 0;
    for(auto &it:North){
        it = it-(it/north_sum)*north_diff;
        new_north+=it;
    }
    
    float south_sum = 0;
    for(auto it:South){
        south_sum+=it;
    }

    float south_diff = south_sum-region[3];
    
    float new_south = 0;
    for(auto &it:South){
        it = it-(it/south_sum)*south_diff;
        new_south+=it;
    }
    
    fstream fout; //for output operations
    // creates a new csv file for output. 
    fout.open("output.csv", ios::out | ios::app); 
    
    int i = 1; 
    for(auto it:East){
        fout<<"E"<<to_string(i)<<","<<to_string(it)<<"\n";
        i++;
    }
    
    i = 1;
    for(auto it:West){
        fout<<'W'<<to_string(i)<<","<<to_string(it)<<"\n";
        i++;
    }
    i = 1;
    for(auto it:North){
        fout<<'N'<<to_string(i)<<","<<to_string(it)<<"\n";
        i++;
    }
    i = 1;
    for(auto it:South){
        fout<<'S'<<to_string(i)<<","<<to_string(it)<<"\n";
        i++;
    }
    
    return 0;
}