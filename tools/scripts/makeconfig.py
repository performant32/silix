#TODO: have fun lil bro

default_yes = 'y';
default_no = 'n';

def ask_information():
    print("Answer with y/n");

    file = open(".main.smk", "w")

    is_valid = False;

    while True:
        is_debug = input("Is Debug? (y)");
        if(is_valid_answer(is_debug) == False):
            if(is_debug != ""):
                inform_invalid_answer();
                continue;
            is_debug = default_yes;
        file.write(f"BUILD_TYPE:={'debug' if is_yes(is_debug) else ''}\n");
        file.write(f"BOOT_FLAGS+={'-s -S' if is_yes(is_debug) else ''}\n");
        break;

    while True:
        is_graphic = input("Is graphic(qemu)? (y)");
        if(is_valid_answer(is_graphic) == False):
            if(is_graphic != ""):
                inform_invalid_answer();
                continue;
            is_graphic = default_yes;
        file.write(f"BOOT_FLAGS+={'-nographic' if not is_yes(is_graphic) else ''}\n");
        break;

    file.close();

def is_yes(answer):
    return answer == 'y';

def inform_invalid_answer():
    print("Must enter a valid answer: y/n");

def is_valid_answer(answer):
    if(answer == 'y' or answer == 'n'):
        return True;
    return False;
if(__name__ == "__main__"):
    ask_information();
