#include <iostream>
#include <string>

using namespace std;

class Cat {

  string name;

public:
    //constructor1
    Cat(string newName){
        cout << "Cat is created: " << name << endl;
       name = newName;
    }
    //constructor2
    Cat(){
        cout << "Cat is created with no name." << endl;
        name = "No Name.";
    }
    //deconstructor
    ~Cat(){
        cout << "Cat is destroyed." << name << endl;
    }

    void miao(){
        cout << "Cat" << name << endl;
    }

};

/*------
   void foo(){
    Cat *p = new Cat("SHAZI");
    //...//
    //delete p;
    p->miao(); // p is a dangling pointer - undefined behavior
}// if we forget to delete constructors, it cause memory leak, so we need smart pointer.
 -----------*/

// use share pointer
void foo(){
    // 1 way to do :
    // 1 step. "shizi" is created 2.step. p is created.
    shared_ptr<Cat> p(new Cat("SHAZI"));// count =1
    {
        shared_ptr<Cat> p2 = p; //count =2
        p2->miao();
    } //p2 goes out out scope, count =1
    p->miao();
    //track how many shared pointers are pointing to the objects.
    cout << p.use_count() << endl; //1

} // Count =0 , at this point, shazi pointer is destroyed.


void foo1(){

    shared_ptr<Cat> ptr1 = make_shared<Cat>("Silly");
    shared_ptr<Cat> ptr2 = make_shared<Cat>("Dummy");

    // Three ways to delete pointer
    // two pointers stored in the stack, and ptr2 is deleted first as it in the top of the stack.
    ptr1 = ptr2; // both of them are pointing to ptr2, 'Silly' is deleted.
    ptr1 = nullptr;
    ptr1.reset();
}

// Custom deleter
void foo2(){
    //Fist method
    //use default deleter: operator delete
    shared_ptr<Cat> ptr1 = make_shared<Cat>("Silly"); // when out of scope, the pointer will automatically deleted.

    //Second method
    //use constructor the create the shared pointer.
    shared_ptr<Cat> ptr2 = shared_ptr<Cat>(new Cat("Dummy"),
                                          [] (Cat* p) {cout << "Custom deleting."; delete p;});


    // Third way, the pointer return an array
    shared_ptr<Cat> ptr3(new Cat[3]); // cat[1] cat[2] have memory leaks, as only cat[3] pointer is deleted when
    // going out of the scope.

    // use custom deleter
    shared_ptr<Cat> ptr4(new Cat[4], [](Cat* p){cout << "Custom deleting."; delete[] p;});

    // KEY POINT
    // if we use shared pointer, it would be better to avoid the  raw pointer, such as:
   // Cat* c = ptr1.get();

}


int main() {

    //foo();
    // The better way to create shared pointer.
    shared_ptr<Cat> c = make_shared<Cat>("DongMei!"); // safe way to create shared pointer.
    c->miao();

    //foo1();
    foo2();
    return 0;
}