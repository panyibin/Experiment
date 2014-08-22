using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        class Person
        {
            string name;
            int age;
            public string Name
            {
                get{return name;}
                set{name = value;}
            }

            public string Name { get; set; }

            private string gender;

            public string Gender
            {
                get { return gender; }
                set { gender = value; }
            }
            
            public int Age
            {
                get
                {
                    return age;
                }

                set
                {
                    if(value >= 0 && value < 200)
                    {
                        age = value;
                    }
                    else
                    {
                        age = 25;
                    }
                }
            }

            public Person(string name, int age)
            {
                this.name = name;
                this.age = age;
            }
        }
        static void Main(string[] args)
        {
            Name = "M$";
            Age = 12;

            Person person = new Person("Google", 10);

            person.Age = 100000;


            Console.WriteLine(person.Name + "\n" + person.Age.ToString());
            Console.WriteLine(Name + "\n" + Age.ToString());

            Console.ReadLine();



        }

        public static int Age { get; set; }

        public static string Name { get; set; }
    }
}
