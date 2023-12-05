#include <iostream>
#include <string>


class Person
{
    public:

    Person(std::string name, std::string gender, int age) {}
    ~Person() {}

    std::string getName()
    {
        return name;
    }

    std::string getGender()
    {
        return gender == 0 ? "man" : "woman";
    }

    void work ()
    {
        if (18 <= age && age <= 50)
        {
            std::cout << name << "is working very hard!" << std::endl;
        }
        else 
        {
            std::cout << name << "can't work any more!" << std::endl;
        }
    }

    private:
    std::string name;
    unsigned int age;
    int gender;

};

int main()
{
     std::string persionGender = "man";
    //  Person personNf;
    // Person 
    // return 0;
}