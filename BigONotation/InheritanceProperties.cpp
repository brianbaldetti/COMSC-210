#include <iostream>
using namespace std;
class  A
{
protected:
    int A_Var;
public:
    A(int val = 10)
    {
        A_Var = val;
        cout << "A constructor: A_Var = " << A_Var << endl;
    }
    
    int getVar()
    {
        cout << "A::getVar = ";
        return A_Var;
    }
    
    /*
    virtual int getVar()
    {
        cout << "A::getVar = ";
        return A_Var;
    }
     */
    
};
 
class  B : public A  // Change public to protected or private and see what can happen
{
private:
    int B_Var;
public:
    B(int val = 100)
    {
        B_Var = val;
        cout << "B constructor: B_Var = " << B_Var << endl;
    }
    int getVar()
    {
        cout << "B::getVar = ";
        return B_Var;
    }
};
 
int main()
{
    /*
     Step 1:
     Predict the output
     */
    
    
    
    cout << "Orginal output:" << endl;
    cout  << endl << "\\1\\" << endl;
       B bObj;
    
       cout <<  endl << "\\2\\" << endl;
       cout << bObj.getVar()<< endl;
    
       cout  << endl << "\\3\\" << endl;
       B *bPtr = nullptr;
       bPtr = &bObj;
       cout << bPtr->getVar() << endl;
    
       cout  << endl << "\\4\\" << endl;
    
        A *aPtr = nullptr;
        aPtr = &bObj;
        cout << aPtr->getVar() << endl;
     
    
   /*
Step 2:
    In Part 4 the called getVar() function is of Class A while the getVar() in Part 3 is of Class B. Can you explain the reason why?
    
Answer
    You get:
    100
    100
    10
    is returned
    */
    
    /*
Step 3:
    Comment out the getVar() function in Class A and compile again. Can it compile?
     
Answer
     No, because the A pointer doesn't know what to reference.
     */
    
    /*
Step 4
     Change int getVar() in Class A to virtual int getVar() Compile and run the program. What will you get?
    
Answer
     You get:
     100
     100
     100
     
     */
    

    /*
    cout  << endl << "Creating B object:" << endl;
    cin.ignore();
    B bObj;
    cin.ignore();
    
    cout << "First A constructor is called." << endl;
    cout << "Next B constructor is called." << endl;
    cout << "This is due to inheritance. Why?\n";
 
    cout <<  endl << "Calling B object 'getVar()' function:" << endl;
    cin.ignore();
    cout << bObj.getVar()<< endl;
    cin.ignore();
    
    cout << "When 'getVar()' is called when referencing B object the value '100' is returned." << endl;
    cout << "This is due to the reference to B object. Object type determines call.\n";
 
    cout  << endl << "Calling B object pointer using 'getVar()' function:" << endl;
    cin.ignore();
    B *bPtr = nullptr;
    bPtr = &bObj;
    cout << bPtr->getVar() << endl;
    cin.ignore();
    
    cout << "When 'getVar()' is called when referecning a B object pointer the value '100' is returned." << endl;
    cout << "Again this is due to the object type reference used to make the call." << endl;
 
    cout  << endl << "Calling B object pointer using an A pointer:" << endl;
    cin.ignore();
    A *aPtr = nullptr;
    aPtr = &bObj;
    cout << aPtr->getVar() << endl;
    cin.ignore();
    
    cout << "When the 'getVar()' function is called the value 10 is returned." << endl;
    cout << "However this can be changed." << endl;
 
  */
    return 0;
}
