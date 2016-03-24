/**
 * description: splits the string at the ' '
 * input: a single string
 * output: a vector of strings --> where each element is a word
 **/
vector<string> splitString(string str) //this may be used on the server side too
{
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words
    
    while (ss >> buf)
        tokens.push_back(buf);
    
    for(int i=0; i<tokens.size(); i++)
    {
        cout<<tokens[i]<<endl;
    }
    return tokens;
}
/**
 * For the control robot menu item, this function checks if the user input is reasonble (ie it has the correct format and a feasible power level
 * input: a vector (the user's input)
 *        the expected size of the vector (it should either be 1 or 2)
 * output: true if the input is reasonable; false otherwise
 **/
bool checkUserInput(vector<string> input, int numArguments)
{
    if(input.size()!=numArguments){return false;}
    else if(input.size()==2) //if the power level was specified
    {
        int pow1=atoi(input[1].c_str()); //checking if the power levels are acceptable
        if(pow1<-127 || pow1>127)
        {
            cout<<"incorrect power input: power level ranges from -127 to 127"<<endl;
            return false; //power needs to be in the -127-127
        }
        else{return true;}
    }
    return true; //if it's the correct # of arguments the input is fine
}
/**
 * Input: the user input (should be a 'Y' or an 'N')
 *        a boolean that is true when the user enter a single character and false otherwise
 *
 *  Output: false if the user says no ('N') true otherwisse
 **/
bool confirm(char userConfirm, bool valid)
{
    while((!valid) || (userConfirm!='Y' && userConfirm!='y' && userConfirm!='N' && userConfirm!='n'))
    {
        cout<<"Please input 'Y' or 'N'"<<endl;
        if(!valid){while ( getchar() != '\n' );} //flusing input buffer
        cin>>userConfirm;
        valid = getchar() == '\n' ? true : false;
    }
    if(userConfirm=='N' || userConfirm == 'n')
    {
        cout<<"run again with different arguments"<<endl;
        return false;
    }
    else{return true;} //user confirmed with 'Y'
    
}
