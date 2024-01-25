#include <iostream>
#include <vector>

// Базовий клас команди
class Command {
public:
    virtual void execute() const = 0;
    virtual ~Command() = default;
};

// Конкретна команда
class ConcreteCommand : public Command {
public:
    ConcreteCommand(const std::string& message) : message_(message) {}

    void execute() const override {
        std::cout << "ConcreteCommand: " << message_ << "\n";
    }

private:
    std::string message_;
};

// Об'єкт, що викликає команду
class Invoker {
public:
    void setCommand(std::shared_ptr<Command> command) {
        command_ = command;
    }

    void executeCommand() const {
        if (command_) {
            command_->execute();
        }
        else {
            std::cout << "Invoker: No command set\n";
        }
    }

private:
    std::shared_ptr<Command> command_;
};

// Об'єкт, який отримує команду та виконує її
class Receiver {
public:
    void performAction(const std::string& action) const {
        std::cout << "Receiver: Performing action '" << action << "'\n";
    }
};

// Команда, яка пов'язується з конкретним отримувачем
class ConcreteCommandWithReceiver : public Command {
public:
    ConcreteCommandWithReceiver(std::shared_ptr<Receiver> receiver, const std::string& action)
        : receiver_(receiver), action_(action) {}

    void execute() const override {
        if (receiver_) {
            receiver_->performAction(action_);
        }
        else {
            std::cout << "ConcreteCommandWithReceiver: No receiver set\n";
        }
    }

private:
    std::shared_ptr<Receiver> receiver_;
    std::string action_;
};

int main() {
    // Використання паттерна "Команда"
    std::shared_ptr<Command> command1 = std::make_shared<ConcreteCommand>("Command 1");
    std::shared_ptr<Command> command2 = std::make_shared<ConcreteCommand>("Command 2");

    Invoker invoker;
    invoker.setCommand(command1);
    invoker.executeCommand();

    invoker.setCommand(command2);
    invoker.executeCommand();

    // Використання команди з отримувачем
    std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>();
    std::shared_ptr<Command> commandWithReceiver = std::make_shared<ConcreteCommandWithReceiver>(receiver, "Custom Action");

    invoker.setCommand(commandWithReceiver);
    invoker.executeCommand();

    return 0;
}
