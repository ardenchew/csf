#include <iostream>
#include <stdio.h>
#include <fstream>

#include "error.h"
#include "process.h"

//opcode list

int main(int argc, char* argv[]) {

    if (argc > 3)
        return get_error(1);

    FILE * rfp = (argc == 1) ? stdin : fopen(argv[1],"r");
    FILE * ofp = (argc != 3) ? stdout : fopen(argv[2],"w");

    if (rfp == NULL)
        return get_error(2);

    if (ofp == NULL)
        return get_error(3);
   
    return process(rfp, ofp);

}

/*

    char c = fgetc(rfp);
    std::string cur_label = "";
    bool label_flag = 0;

    unsigned char mem[256];
    std::map<std::string, unsigned char> label_dict;
    std::map<int, std::string> label_args; 

    std::string cur_opcode;

    while (c != EOF) {
        
        if (!(isspace(c))) { // if label
            label_flag = 1; 

            if (((c > 90) && (c < 97)) || (c < 65) || (c > 122)) 
                return get_error(7);

            cur_label += c; 
            c = fgetc(rfp);

            while (c != 58) {
                if ((c < 48) || (c > 122) || ((c > 57) && (c < 65)) || ((c > 90) && (c != 95) && (c < 97)))
                    return get_error(7);
                cur_label += c;
                c = fgetc(rfp);
            }
        std::cout << cur_label << std::endl;
        }

        while (!(isspace(c))) {
        //process for getting byte


        //if label flag add byte to dict
        //else add byte to mem
        
   
    //reset all

    c = getc(rfp);
    cur_label = ""; //should be first one of new line
    label_flag = 0;
    }

    return 0;

}
**/
