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

            //public string Name { get; set; }

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

            List<Person> people = new List<Person>();

            Person p1 = new Person("p1", 15);
            Person p2 = new Person("p2", 16);
            Person p3 = new Person("p3", 17);
            Person p4 = new Person("p4", 18);
            Person p5 = new Person("p5", 19);
            Person p6 = new Person(null, 20);

            people.Add(p1);
            people.Add(p2);
            people.Add(p3);
            people.Add(p4);
            people.Add(p5);
            people.Add(p6);

            const int age = 17;

            //IEnumerable<Person> results = people.Where(delegate(Person p) { return p.Age > age; });
            IEnumerable<Person> results = people.Where(p => (p.Age > age));

            Console.WriteLine("people older than 17:");
            foreach(Person p in results)
            {
                Console.WriteLine(p.Name ?? "oh my god");
            }

            Console.ReadLine();



        }

        public static int Age { get; set; }

        public static string Name { get; set; }
    }
}
