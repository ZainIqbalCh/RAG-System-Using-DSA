#include <iostream>
#include <fstream>
#include <vector>
#include<cctype>
#include <string>
#include <json/json.h>
#include<sstream>
#include<iomanip>
#include<fstream>
#include <unordered_map>
#include <regex>
#include<windows.h>
using namespace std;

class stacknode {
public:
    string emailaddress;
    string emailtext;
    string response;
    stacknode* next;

    stacknode(string add, string email, string resp) {
        emailaddress=add;
        emailtext=email;
   response=resp;
   next = NULL;
    }

};

class stack {
private:
   stacknode* head;
public:
    stack() {
        head = NULL;
    }
    void push(string add, string email, string resp) {
        stacknode* n = new stacknode(add, email, resp);
        if (head == NULL) {
            head = n;
            return ;
        }
        n->next = head;
        head = n;
    }
    bool isempty() {
        if (head == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    stacknode* pop() {
      
        if (head == NULL) {
            return NULL;
        }
        stacknode* topop = head;  
        head = topop->next;        
        topop->next = NULL;        
        return topop;

    }
}st;

class diamond {
private:
    int i;
    int j;
    int k;
public:
    void d()
    {

        system("color 0A");
        for (i = 1; i < 18; i++)
        {
            for (j = 1; j <= 20 - i; j++)
            {
                cout << setw(3) << " ";
            }
            for (k = 1; k <= 2 * i - 1; k++) {

                cout << setw(3) << "*";

            }
            cout << endl;
        }
        cout << "\t-----------------------------Welcome To Air University Information Centre-----------------------------" << endl;
        for (i = 18; i >= 1; i--)
        {

            for (j = 1; j <= 20 - i; j++)
            {
                cout << setw(3) << " ";
            }
            for (k = 1; k <= 2 * i - 1; k++) {
                cout << setw(3) << "*";

            }
            cout << endl;
        }
    }

};

class node
{
public:
    string name;
    vector<node*> child;

    node(string v) : name(v) {}
};
bool insertion(node* root, string parent, string data)
{
    if (!root)
    {
        return false;
    }
    if (root->name == parent)
    {
        node* new_child = new node(data);
        root->child.push_back(new_child);
        return true;
    }
    for (auto c : root->child)
    {
        if (insertion(c, parent, data))
        {
            return true;
        }
    }
    return false;
}

node* search(node* root, string parent, const string& target)
{
    if (root == nullptr)
        return nullptr;

    node* result = nullptr;

    if (parent == "department")
        result = root->child[0];
    else if (parent == "society")
        result = root->child[1];
    else
        return nullptr;

    for (auto& num : result->child)
    {
        if (num->name == target)
            return num;
    }

    return nullptr;
}
struct aa {
    bool dep;
    bool soci;

    void setbool(bool department, bool society) {
        dep = department;
        soci = society;
    }
    void getbool() {
        cout << "department " << dep << " society " << soci << endl;
    }
};
aa a;
string parsesection(const string& emailBody)
{
    vector<string> departments =
    {
        "ai", "bsai", "artificial intelligence", "artificial int", "intelligence",
     "bachelor of science in artificial intelligence",
        // Cyber security variations
        "cyber security", "cyber",
         "bachelor of science in cyber security",
         // Gaming variations
         "gaming", "game dev", "game development", "game design",
         "game industry", "gaming industry", "gaming tech", "game programming", "bachelor of science in gaming",
         // Software engineering variations
         "software engineering", "se", "software eng", "software development",
         "software dev", "system engineering",
         // Data science variations
         "data science", "ds",  "data analysis", "data analytics", "data scientist",
         "data engineering",  "machine learning", "statistical analysis",
         // CS variations
         "cs", "computer science",
         "comp sci"
    };
    vector<string>society =
    {
        "augdsc", "aumlsa", "audas", "auses" ,"air university google developer student club",
        "air university microsoft learn student ambassodar","air university data and ai society",
        "air university software engineering society"
    };
    bool isDepartment = false;

    bool issociety = false;
    for (const string& keyword : departments)
    {
        regex re("\\b" + keyword + "\\b");
        if (regex_search(emailBody, re))
        {
            isDepartment=true;
            break;
        }
    }


    for (const string& keywor : society)
    {
        regex ree("\\b" + keywor + "\\b");
        if (regex_search(emailBody, ree)) {
            issociety=true;
            break;
        }
    }

    a.setbool(isDepartment,issociety);
    if (isDepartment) {
        return "department";
    }
    else if(issociety) {
        return "society";
    }
    return " ";
}

string parsedept(const string& emailBody)
{
    vector<string> keywords =
    {
        "ai", "bsai", "artificial intelligence", "artificial int", "intelligence",
    "bachelor of science in artificial intelligence",

        // Cyber security variations
        "bs cyber security","cyber security", "cyber", "bachelor of science in cyber security",

        // Gaming variations
        "gaming", "game dev", "game development", "game design","bs gaming",
        "game industry", "gaming industry", "gaming tech", "game programming", "bachelor of science in gaming",

        // Software engineering variations
        "software engineering", "se", "software eng", "software development",
        "software dev", "system engineering","bsse",

        // Data science variations
        "data science", "ds", "data analysis", "data analytics", "data scientist",
        "data engineering", "machine learning", "statistical analysis","bsds",

        // CS variations
        "cs", "computer science", "comp sci" ,"bscs"
    };
    for (const string& keyword : keywords)
    {
        string pattern = "\\b" + keyword + "\\b";
        regex re(pattern, regex::icase);
        if (regex_search(emailBody, re)) {
            return keyword;
        }
    }
    return "";
}

string parsesociety(const string& emailBody)
{
    vector<string> keywords = { "augdsc", "aumlsa", "audas", "auses" ,"air university google developer student club",
        "air university microsoft learn student ambassodar","air university data and ai society",
        "air university software engineering society" };
    for (const string& keyword : keywords)
    {
        string pattern = "\\b" + keyword + "\\b";
        regex re(pattern, regex::icase);
        if (regex_search(emailBody, re))
        {
            return keyword;
        }
    }
    return "";
}


string generateResponse(node* gen)
{
    if (!gen)
    {
        return "Sorry, the requested information is not available.\n";
    
    }

    stringstream response;

    for (node* child : gen->child)
    {
        response << child->name << endl;
    }
    return "Information about "+ gen->name + ":\n"+ response.str();
}

string mapping(string target)
{
    unordered_map<string, string> reverseMapping;
    // AI and variations
    reverseMapping["ai"] = "ai";
    reverseMapping["bsai"] = "ai";
    reverseMapping["artificial intelligence"] = "ai";
    reverseMapping["artificial int"] = "ai";
    reverseMapping["bachelor of science in artificial intelligence"] = "ai";
    reverseMapping["bs-ai"] = "ai";
    reverseMapping["ai tech"] = "ai";

    // Cyber security and variations
    reverseMapping["bachelor of science in cyber security"] = "cyber security";
    reverseMapping["cyber security"] = "cyber security";
    reverseMapping["cyber"] = "cyber security";
    reverseMapping["security"] = "cyber security";
    reverseMapping["infosec"] = "cyber security";
    reverseMapping["network security"] = "cyber security";
    reverseMapping["it security"] = "cyber security";
    reverseMapping["digital security"] = "cyber security";
    reverseMapping["computer security"] = "cyber security";
    reverseMapping["bscys"] = "cyber security";
    reverseMapping["bs-cys"] = "cyber security";




    // Gaming and variations
    reverseMapping["bachelor of science in gaming"] = "gaming";
    reverseMapping["gaming"] = "gaming";
    reverseMapping["game dev"] = "gaming";
    reverseMapping["game development"] = "gaming";
    reverseMapping["game design"] = "gaming";
    reverseMapping["video games"] = "gaming";
    reverseMapping["game industry"] = "gaming";
    reverseMapping["gaming industry"] = "gaming";
    reverseMapping["gaming tech"] = "gaming";
    reverseMapping["game programming"] = "gaming";
    reverseMapping["bachelor of science in computer games development"] = "gaming";
    reverseMapping["bs-cgd"] = "gaming";
    reverseMapping["bscgd"] = "gaming";
    // Gaming variations


    // Software Engineering and variations
    reverseMapping["bachelor of science in software engineering"] = "se";
    reverseMapping["software engineering"] = "se";
    reverseMapping["se"] = "se";
    reverseMapping["software eng"] = "se";
    reverseMapping["bsse"] = "se";
    reverseMapping["bs-se"] = "se";



    reverseMapping["augdsc"] = "augdsc";
    reverseMapping["aumlsa"] = "aumlsa",
        reverseMapping["audas"] = "audas",
        reverseMapping["auses"] = "auses";

    reverseMapping["air university google developer student club"] = "augdsc";
    reverseMapping["air university microsoft learn student ambassodar"] = "aumlsa";
    reverseMapping["air university data and ai society"] = "audas";
    reverseMapping["air university software engineering society"] = "auses";

    // Data Science and variations
    reverseMapping["bachelor of science in data science"] = "ds";
    reverseMapping["data science"] = "ds";
    reverseMapping["ds"] = "ds";
    reverseMapping["bsds"] = "ds";
    reverseMapping["bs-ds"] = "ds";

    // Computer Science and variations
    reverseMapping["cs"] = "cs";
    reverseMapping["bscs"] = "cs";
    reverseMapping["bs-cs"] = "cs";
    reverseMapping["computer science"] = "cs";
    reverseMapping["bachelor of science in computer science"] = "cs";
    reverseMapping["comp sci"] = "cs";

    if (reverseMapping.find(target) != reverseMapping.end())
    {
        return reverseMapping[target];
    }

}

node* creating_the_tree()
{
    ifstream jsonfile("data11.json");
    if (!jsonfile.is_open())
    {
        cout << "Failed to open the file!" << endl;
        return 0;
    }

    Json::CharReaderBuilder reader;
    Json::Value data;
    string e;
    if (!Json::parseFromStream(reader, jsonfile, &data, &e))
    {
        cerr << "Error parsing the JSON file: " << e << endl;
        return 0;
    }
    jsonfile.close();

    string root_main = data.getMemberNames()[0];
    node* root = new node(root_main);

    Json::Value departments = data["Air University"]["Departments"];
    insertion(root, root_main, "Departments");
    for (auto& department : departments.getMemberNames())
    {
        insertion(root, "Departments", department);

        string details = departments[department]["INFO"].asString();
        insertion(root, department, details);
    }

    Json::Value societies = data["Air University"]["Societies"];
    insertion(root, root_main, "Societies");
    for (auto& society : societies.getMemberNames())
    {
        insertion(root, "Societies", society);

        string details = societies[society]["INFO"].asString();
        insertion(root, society, details);
    }
    return root;
}
void print(node* root, int level)
{
    if (root == NULL)
        return;
    for (int i = 0; i < level; i++)
    {
        cout << "   ";
    }
    cout << root->name << endl;
    for (auto child : root->child)
    {
        print(child, level + 1);
    }
}
bool checkenailadress(string email) {

    if (email.length() < 6) {
        return false;
    }
    int position = email.find("@gmail.com");
    if (position != string::npos) {
        return true;
    }
    return false;

}

void systempause() {
    system("Pause");
    system("Cls");
}

void write_to_file(string output) {
    ofstream outputfile(output, ios::app);
    while (!st.isempty()) {
        stacknode* topop = st.pop();
        outputfile <<"Email Address:/n" << topop->emailaddress << endl;
        outputfile << "Email Content:/n" << topop->emailtext << endl;
        outputfile << "Response:/n" << topop->response << endl;
        outputfile << endl;
    }
}

int main()
{
    diamond d;
    d.d();
    systempause();
 

    node* root = creating_the_tree();
    string filename = "history.txt";
    ofstream outputfile(filename,ios::out);
    do{
    cout << "Enter Your Email Address :";
    string emailaddress;
    getline(cin, emailaddress);
    bool validemail = checkenailadress(emailaddress);
    if (validemail)
    {
        cout << "Enter Your Email Body :";
        string emailbody;
        getline(cin, emailbody);

        string email = "";
        for (char& c : emailbody)
        {
            c = tolower(c);
            email = email + c;
        }
     
        string section = parsesection(email);
      
        string target;
       
        if (section == "department")
        {
            target = parsedept(emailbody);
        }
        else
        {
            target = parsesociety(emailbody);
        }
    
        string mapped = mapping(target);
      

        node* result = search(root, section, mapped);
       
       string response =generateResponse(result);
       cout << "Details about " << response<<endl;
       st.push(emailaddress, emailbody, response);
       write_to_file(filename);



    }
    else {
        cout << "Invalid Email Address" << endl;
    }
}while (true);
}
