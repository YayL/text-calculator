#include <bits/stdc++.h>

std::vector<int*> parentheses;
char operatorTypes[] {'+', '-', '*', '/', '^', '%'};

bool error(std::string errorMessage, std::string str = "", int index = 0, bool showIndex = false){
    if(str != "")
        std::cout << str << std::endl;
    index--;
    for(int i = 0; i < index; i++){
        std::cout << ' ';
    }
    std::cout << '^' << std::endl;
    std::cout << errorMessage << (showIndex ? std::to_string(index) : "") << std::endl;
    return false;
}

bool calculateParentheses(std::string& str){
    parentheses.clear();
    std::stack<int> par;
    std::string tok;
    int* temp;

    for(int i = 0; i < str.length(); i++){
        if(str[i] == '(')
            par.push(i);

        else if(str[i] == ')')
        {
            if(par.size() == 0)
                return error("Not matching closing parentheses at ", str, i + 1, true);

            temp = (int*) malloc(sizeof(int) * 2);
            temp[0] = par.top();
            temp[1] = i;
            parentheses.push_back(temp);
            par.pop();
        }
    }
    if(par.size() == 1)
    {
        temp = (int*) malloc(sizeof(int) * 2);
        temp[0] = par.top();
        temp[1] = str.length();
        parentheses.push_back(temp);
    }
    else if(par.size() > 1){
        return error("Not matching parentheses at ", str, par.top() + 1, true);
    }
    return true;
}

bool replaceStr(std::string& str, std::string repl, const int start, const int& end) {
    size_t start_pos = start;
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, (end - start), repl);
    return true;
}

void operation(char opr, std::string x, std::string y, int& result){

    switch(opr){
        case '+':
            result = std::stoi(x) + std::stoi(y); break;
        case '-':
            result = std::stoi(x) - std::stoi(y); break;
        case '*':
            result = std::stoi(x) * std::stoi(y); break;
        case '/':
            result = std::stoi(x) / std::stoi(y); break;
        case '^':
            result = pow(std::stoi(x), std::stoi(y)); break;
        case '%':
            result = std::stoi(x) % std::stoi(y); break;
    }

    //std::cout << stoi(x) << " " << opr << " " << stoi(y) << " = " << result << std::endl;

}

void calculate(std::string& str, int start, int end){

    std::string token = str.substr(start + 1, (end - start - 1));
    int result = 0;

    std::cout << token << std::endl;

    for(int i = 0; i < token.length(); i++){
        for(char c : operatorTypes){
            if(token[i] == c){
                if(i != 0){
                    operation(c, token.substr(0, i), token.substr(i + 1, token.length() - i), result);
                    if(!replaceStr(token, std::to_string(result), 0, token.length() - i + 1))
                        error("There was an unknown error. Attempt to replace end of string.");
                    i = 0;
                    std::cout << result << std::endl;
                    break;
                }else{
                    error("There was a syntax error at ", str, start, true);
                    return;
                }
            }
        }
    }

    if(!replaceStr(str, std::to_string(result), start, end + 1))
        error("There was an unknown error. Attempt to replace end of string.");
}

bool calculateParenthesis(std::string& str){
    int max = parentheses.size();
    
    while(parentheses.size() != 0 || --max != 0){
        std::cout << "Parentheses: " << parentheses[0][0] << " -> " << parentheses[0][1] << std::endl;
        calculate(str, parentheses[0][0], parentheses[0][1]);
        free(parentheses[0]);
        calculateParentheses(str);
        //std::cout << str << std::endl;
    }
    calculate(str, 0, str.length());

    return true;
}

int main(){

    std::string expression = "(", temp;
    getline(std::cin, temp);
    std::stringstream ss(temp);

    while(getline(ss, temp, ' ')){
        if(temp.length() != 0)
            expression += temp;
    }
    expression += ")";

    //std::cout << expression << std::endl;
    
    if(!calculateParentheses(expression))
        return 0;

    calculateParenthesis(expression);

    //std::cout << expression << std::endl;

    std::getchar();

}