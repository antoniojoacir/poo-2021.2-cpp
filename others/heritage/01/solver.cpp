#include <iostream>

class First {
	std::string name;
public:
	// mostra apenas o $name da classe
	First(std::string name = "") : name(name) {
		//std::cout << this->name << " is created" << std::endl; 
	}
	virtual ~First() {
		//std::cout << this->name << " is destroyed" << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& stream, const First& first) {
		stream << first.name;
		return stream;
	}

	virtual std::string get_name() const {
		return this->name;
	}

	virtual void walk() {
		std::cout << "is walking // first class\n";
	}
};

class Second : public First {
	int age;
public:
	// mostra o $name e $age da classe
	Second(std::string name = "", int age = 0) : First(name), age(age) {
		//std::cout << this->get_name() << " : " << this->age << " is created" <<std::endl;
	}

	virtual ~Second() {
		//std::cout << this->get_name() << " : " << this->age << " is destroyed" << std::endl;
	}

	virtual int get_age() const {
		return this->age;
	}

	virtual void walk() {
		std::cout << "is walking // second class\n";
	}

	virtual void rest() {
		std::cout << "is resting // second class\n";
	}

	friend std::ostream& operator<<(std::ostream& stream, const Second& second) {
		stream << second.get_name() << " : " << second.age;
		return stream;
	}
};

class Third : public Second {
	bool is_married { false };
public:

	Third(std::string name = "", int age = 0, std::string married = "") :
	Second(name, age), is_married(married == "yes") {
		//std::cout << this->get_name() << " : " << this->get_age() << " : " << (this->is_married ? "yes" : "no") << "\n";
	}

	virtual ~Third() {
		//std::cout << this->get_name() << " : " << this->get_age() << " : " << (this->is_married ? "yes" : "no") << "\n";
	}

	virtual void walk() {
		std::cout << "is walking // third class\n";
	}

	virtual void rest() {
		std::cout << "is resting // third class\n";
	}

	friend std::ostream& operator<<(std::ostream& stream, const Third& third) {
		stream << third.get_name() << " : " << third.get_age() << " : " << (third.is_married ? "congratulations" : "keep trying") << "\n";
		return stream;
	}
};

int main() {
	First first("Joa");

	Second second("Joa", 20);

	Third third("Joa", 20, "no");
	
	Second _third_ = third; // copiando uma class Third(name, age, bool) para uma class Second(name, age)
	_third_.walk();
	_third_.rest();
	First _second_ = second; // copiando uma class Second(name, age) para uma class First(name)
	_second_.walk();
	
	std::cout << first << std::endl;
	std::cout << second << std::endl;
	std::cout << third << std::endl;

	std::cout << _third_ << std::endl;
	std::cout << _second_ << std::endl;
	
}