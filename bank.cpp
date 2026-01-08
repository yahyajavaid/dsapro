#include <iostream>
#include <fstream>
using namespace std;
struct trastack{
    string type;
    double amount;
};
class account{
    private:
    int accountnumber;
    string name;
    double balance;
    int pin;
    bool hasdebicard;
    bool hascrecard;
    double dcnumber;
    double ccnumber;
    trastack transhis[5];
    int stacktop;
    public:
    //Default Constructorss Formation
    account(){
        accountnumber=0;
        name="";
        balance=0;
        pin=0;
        hasdebicard=false;
        hascrecard=false;
        dcnumber=0;
        ccnumber=0;
        stacktop=-1;
    }
    //Parameterized Constructor
    account(int accno,string nam,double bal,int pin,bool hasdebicard,bool hascrecard,double dcnumber,double ccnumber,int stacktop){
        accountnumber=accno;
        name=nam;
        balance=bal;
        this->pin=pin;
        this->hascrecard=hascrecard;
        this->hasdebicard=hasdebicard;
        this->stacktop=stacktop;
        this->dcnumber=dcnumber;
        this->ccnumber=ccnumber;

    }
    //setter Functions
    int getstacktop(){
    return stacktop;
    }

    string gettranstype(int index){
    if(index >= 0 && index <= stacktop){
        return transhis[index].type;
    }
    return "";
    }

    double gettransamount(int index){
    if(index >= 0 && index <= stacktop){
        return transhis[index].amount;
    }
    return 0;
    }
    void setaccountnumber(int accountnumber){
        this->accountnumber=accountnumber;
    }
    void setcrenum(double ccnumber){
        this->ccnumber=ccnumber;
    }
    void setdebinum(double dcnumber){
        this->dcnumber=dcnumber;
    }
    void setdebi(bool hasdebicard){
        this->hasdebicard=hasdebicard;
    }
    void setcre(bool hascrecard){
        this->hascrecard=hascrecard;
    }
    void setname(string nam){
        name=nam;
    }
    void setbalance(int bal){
        balance=bal;
    }
    //getter functions
    int getpin(){
        return pin;
    }
    bool hasdebi(){
        return hasdebicard;
    }
    bool hascredi(){
        return hascrecard;
    }
    double ccnumberfun(){
        return ccnumber;
    }
    double dcnumberfun(){
        return dcnumber;
    }
    int getaccountnumber(){
        return accountnumber;
    }
    double getbalance(){
        return balance;
    }
    string getname(){
        return name;
    }
    void depositfunc(double amount){
        if(amount>0){
            balance=balance+amount;
            cout<<"Deposit Confirmed you deposited "<<amount<<"."<<endl;
        }else{
            cout<<"Invalid amount entered"<<endl;
        }
    }
    void withdrawfunc(double amount){
        if(amount>0 && balance>=amount){
            balance=balance-amount;
            cout<<"Withdrawl Confirmed"<<endl;
        }else{
            cout<<"Balance is Low or you have entered invalid amount"<<endl;
        }
    }
    void displayinfo(){
        cout<<"The name of the account holder is "<<name<<endl;
        cout<<"The balance of the account is "<<balance<<endl;
        cout<<"The account Number is "<<accountnumber<<endl;
    }
    void addtrans(string type,double amount){
        if(stacktop<4){
            stacktop++;
            transhis[stacktop].amount=amount;
            transhis[stacktop].type=type;
        }else{
            for(int i=0;i<4;i++){
                transhis[i]=transhis[i+1];
            }
        transhis[stacktop].type=type;
        transhis[stacktop].amount=amount;
        }
    }
    void showtrans(){
        if(stacktop<0){
            cout<<"No transaction were found "<<endl;
        }else{
            int i=stacktop;
            while(i>=0){
                cout<<"This is transaction "<<endl;
                cout<<transhis[i].amount<<endl;
                cout<<transhis[i].type<<endl;
                i--;
            }
        }
    }
    void settransaction(int index, string type, double amount){
        if(index >= 0 && index < 5){
            transhis[index].type = type;
            transhis[index].amount = amount;
        }
    }
};
//USE of a Data Structure Specifically LINKED LIST
struct accnode{
    //creating an object from the account Class
    account data;
    accnode *next;
};
class Bank{
    private:
    //the main pointer
    accnode *head;
    public:
    Bank(){
        head=nullptr;
    }
    void createaccount(int accountnumber,string name,double balance,int pin,bool hasdebicard,bool hascrecard,double dcnumber,double ccnumber,int stacktop){
        //create an object in the heap memory
        accnode *acnod=new accnode;
        //use of the constructor to enter the data in the node
        acnod->data=account(accountnumber,name,balance,pin,hasdebicard,hascrecard,dcnumber,ccnumber,stacktop);
        acnod->next=head;
        head=acnod;
    }
    void displayallacc(){
        accnode *temp=head;
        if(head==nullptr){
            cout<<"No account Found "<<endl;
        }else{
            while(temp!=nullptr){
                temp->data.displayinfo();
                temp=temp->next;
            }

        }        
    }
    accnode* searchacc(int searchedaccount){
        //creating a temporary pointer and equaling it to head so that it can point to linked list
        accnode *temp=head;
        while(temp!=nullptr){
            if(temp->data.getaccountnumber()==searchedaccount){
                cout<<"Account Found "<<searchedaccount<<endl;
                return temp;
            }
            temp=temp->next;
        }
        return nullptr;
    }
    void depositbhq(int accountnumber,double amount){
        accnode *foundnodee=searchacc(accountnumber);
        if(foundnodee!=nullptr){
            foundnodee->data.depositfunc(amount);
            foundnodee->data.addtrans("Deposit",amount);
        }
        else{
            cout<<"Account not found "<<endl;
        }
    }
    void withdrawbhq(int accountmumber,double amount){
        accnode *foundednode=searchacc(accountmumber);
        if(foundednode!=nullptr){
            foundednode->data.withdrawfunc(amount);
            foundednode->data.addtrans("Withdraw",amount);
        }
        else{
            cout<<"Account not Found or Error Occured"<<endl;
        }
    }
    void transfermoney(int fromacc,int toacc,double amount,int pin){
        accnode *temp1=searchacc(fromacc);
        accnode *temp2=searchacc(toacc);
        if(temp1==nullptr || temp2==nullptr){
            cout<<"The Sender or The receiver account does not exist "<<endl;
        }
        else{
            if(temp1->data.getpin()==pin){
                if(temp1->data.getbalance()<amount){
                    cout<<"You dont have enough balance "<<endl;
                }else{
                    temp1->data.withdrawfunc(amount);
                    temp2->data.depositfunc(amount);
                    temp1->data.addtrans("Withdraw",amount);
                    temp2->data.addtrans("Deposit",amount);
                    cout<<"Money is deposited "<<endl;
                }
            }else{
                cout<<"You have entered the wrong PIN"<<endl;
            }
        }
    }
    void issuecc(int accountnumber,int pin){
        accnode *temp3=searchacc(accountnumber);
        if(temp3==nullptr){
            cout<<"Account not found "<<endl;
        }else{
            if(temp3->data.getpin()!=pin){
                cout<<"You have entered invalid pin "<<endl;
            }else{
                if(temp3->data.hascredi()==true){
                    cout<<"You already have a credit Card "<<endl;
                }else{
                    if(temp3->data.getbalance()<50000){
                        cout<<"You balance is less than the threshold "<<endl;
                    }else{
                        double cccnum=accountnumber*10000+1111;
                        temp3->data.setcre(true);
                        temp3->data.setcrenum(cccnum);
                        cout<<"Credit card issued with the number "<<cccnum;
                    }
                }
            }
        }
    }
    void issuedc(int accountnumber,int pin){
        accnode *temp5=searchacc(accountnumber);
        if(temp5==nullptr){
            cout<<"Account not found "<<endl;
        }else{
            if(temp5->data.getpin()!=pin){
                cout<<"You have entered an invalid pin "<<endl;
            }else{
                if(temp5->data.hasdebi()==true){
                    cout<<"You already have a debit card "<<endl;
                }else{
                    double dcd=accountnumber*10000+1111;
                    temp5->data.setdebi(true);
                    temp5->data.setdebinum(dcd);
                    cout<<"Debit Card Issued Finally "<<endl;
                }
            }
        }
    }
    void savetofile(){
    ofstream outfile("bankdata.txt");
    if(!outfile){
        cout<<"File does not exist or an error occured "<<endl;
    }else{
        accnode *temp4=head;
        while(temp4!=nullptr){
            outfile<<temp4->data.getaccountnumber()<<endl;
            outfile<<temp4->data.getname()<<endl;
            outfile<<temp4->data.getbalance()<<endl;
            outfile<<temp4->data.getpin()<<endl;
            outfile<<temp4->data.hasdebi()<<endl;
            outfile<<temp4->data.hascredi()<<endl;
            outfile<<temp4->data.dcnumberfun()<<endl;
            outfile<<temp4->data.ccnumberfun()<<endl;
            outfile<<temp4->data.getstacktop()<<endl;  // Save stacktop first
            for(int i = 0; i <= temp4->data.getstacktop() && i < 5; i++){
                outfile<<temp4->data.gettranstype(i)<<endl;
                outfile<<temp4->data.gettransamount(i)<<endl;
                }
            
            temp4=temp4->next;
        }
        outfile.close();
        cout<<"Database updated"<<endl;    
    }
}
    void loadFromFile() {
    ifstream inFile("bankdata.txt");
    if (!inFile) return; 
    
    int an, p;
    string n;
    double b;
    bool hdc, hcc;
    double dcn, ccn;
    int stop;  // stacktop value
    
    while (inFile >> an) { 
        inFile.ignore(); 
        getline(inFile, n); 
        inFile >> b >> p;
        inFile >> hdc >> hcc;
        inFile >> dcn >> ccn;
        inFile >> stop;  // Read stacktop
        accnode *newNode = new accnode;
        newNode->data = account(an, n, b, p, hdc, hcc, dcn, ccn, stop);
        for(int i = 0; i <= stop && i < 5; i++){
            string ttype;
            double tamount;
            inFile.ignore();
            getline(inFile, ttype);
            inFile >> tamount;
            newNode->data.settransaction(i, ttype, tamount);
        }
        
        newNode->next = head;
        head = newNode;
    }
    inFile.close();
}
    void viewTransactionHistory(int accNo, int pin){
        accnode *temp55=searchacc(accNo);
        if(temp55==nullptr){
            cout<<"Account does not exist "<<endl;
        }else{
            if(temp55->data.getpin()==pin){
                temp55->data.showtrans();
            }else{
                cout<<"Wrong Pin entered "<<endl;
            }
        }   
    }
};
int main(){
    Bank ban;
    ban.loadFromFile();
    account acc;
    int choice=0;
    int acnumb;
    int pin;
    int depimon;
    int withmoney;
    double balnumb;
    string namenumb;
    int toac;
    int fromac;
    int tam;
    while(true){
        cout<<"Create Account Press 1 "<<endl;
        cout<<"Deposit Money Press 2 "<<endl;
        cout<<"Withdraw Money Press 3 "<<endl;
        cout<<"Search For Account Press 4 "<<endl;
        cout<<"Transfer money to bank account Press 5"<<endl;
        cout<<"Display all accounts Press 6 "<<endl;
        cout<<"Get credit card For Your account Press 7 "<<endl;
        cout<<"Get Debit Card for your account Press 8 "<<endl;
        cout<<"Get transaction History Press 9"<<endl;
        cout<<"Exit From the Bank Press 10"<<endl;
        cin>>choice;
        

    if(cin.fail()) {
    cin.clear();
    cin.ignore(1000, '\n');  // Clear entire line, not just one character
    cout << "Invalid input. Please enter a number (1-6)." << endl;
    continue;
}
   
        switch (choice)
    {
    case 1:
        cout<<"Enter your mobile number which will act as account number "<<endl;
        cin>>acnumb;
        cout<<"Enter the Name of the accountholder "<<endl;
        cin>>namenumb;
        cout<<"Enter the initial or starting balance can be 0 also "<<endl;
        cin>>balnumb;
        cout<<"Enter your pin "<<endl;
        cin>>pin;
        ban.createaccount(acnumb,namenumb,balnumb,pin,false,false,0,0,-1);
        ban.savetofile();
        cout<<"Account creation successful"<<endl;
        break;
    case 2:{
        cout<<"Enter the account number you want to deposit money in "<<endl;
        cin>>acnumb;
        accnode *temp1=ban.searchacc(acnumb);
        if(temp1!=nullptr){
            cout<<"Enter the pin for the account number "<<acnumb<<endl;
            cin>>pin;
            if(temp1->data.getpin()==pin){
                cout<<"Enter the amount you want to deposit"<<endl;
                cin>>depimon;
                ban.depositbhq(acnumb,depimon);
            }else{
                cout<<"Wrong Pin Entered"<<endl;
            }
        }
        else{
            cout<<"Account not found"<<endl;
            } 
    ban.savetofile();
    break;
}
    case 3:{
    cout<<"Enter the account number you want to withdraw the money from"<<endl;
    cin>>acnumb;
    accnode *temp2=ban.searchacc(acnumb);
    if(temp2!=nullptr){
        cout<<"Enter the pin for the account "<<acnumb<<endl;
        cin>>pin;
        if(temp2->data.getpin()==pin){
            cout<<"Enter the amount you want to withdraw "<<endl;
            cin>>withmoney;
            ban.withdrawbhq(acnumb,withmoney);
        }else{
            cout<<"You have entered wrong Pin"<<endl;
        }
    }else{
        cout<<"Account does not exist "<<endl;
    }
    ban.savetofile();
    break;
}
    case 4:{
    cout<<"Welcome to searchaccount function "<<endl;
    cout<<"Enter the account number you want to search "<<endl;
    cin>>acnumb;
    accnode *temp3=ban.searchacc(acnumb);
    if(temp3!=nullptr){
        cout<<"The account Number you entered exist in our database "<<endl;
        cout<<"The name of the account holder is "<<endl<<temp3->data.getname()<<endl;
        cout<<"The balance of the account is "<<endl<<temp3->data.getbalance()<<endl;
    }
    ban.savetofile();
    break;
}
    case 5:{
        cout<<"Please enter the senderaccount "<<endl;
        cin>>fromac;
        cout<<"Please enter the receiver account "<<endl;
        cin>>toac;
        cout<<"Please enter the amount "<<endl;
        cin>>tam;
        cout<<"Please enter the pin for sending account "<<endl;
        cin>>pin;
        ban.transfermoney(fromac,toac,tam,pin);
        ban.savetofile();

        }
    break;
    case 6:
    cout<<"Welcome to display all account function "<<endl;
    cout<<"The list of all account is as follow "<<endl;
    ban.displayallacc();
    break;
    case 7:
    cout<<"Welcome to Credit Card issuance "<<endl;
    cout<<"Enter the account Number "<<endl;
    cin>>acnumb;
    cout<<"Enter the pin for your account "<<endl;
    cin>>pin;
    ban.issuecc(acnumb,pin);
    ban.savetofile();
    break;
    case 8:
    cout<<"Welcome to Debit Card issuance "<<endl;
    cout<<"Enter the account Number "<<endl;
    cin>>acnumb;
    cout<<"Enter the pin for your account "<<endl;
    cin>>pin;
    ban.issuedc(acnumb,pin);
    ban.savetofile();
    break;
    case 9:
    cout << "Welcome to Transaction History" << endl;
    cout << "Enter account number: " << endl;
    cin >> acnumb;
    cout << "Enter PIN: " << endl;
    cin >> pin;
    ban.viewTransactionHistory(acnumb, pin);
    break;
    break;
    case 10:
    cout<<"Thank you for using our bank "<<endl;
    return 0;
    default:
    cout<<"Enter the amount from 1 to 6 only "<<endl;
        break;
    }
    }    
}