#include "buttons.h"
#include <algorithm>
#include <type_traits>


BaseButton::BaseButton(const int x, const int y, const int width, const int height, const std::string &text):
x(x),y(y),width(width),height(height),text(text){};

int BaseButton::getHeight() {
    return this->height;
}
int BaseButton::getWidth() {
    return this->width;
}

int BaseButton::getX() {
    return this->x;
}

int BaseButton::getY() {
    return this->y;
}


GoBackButton::GoBackButton(const int x, const int y, const int width, const int height, const std::string text,
                           std::vector<BaseButton*>& ButtonsNext):
                           BaseButton(x,y,width,height,text){
    this->NextButtons = ButtonsNext;
}

void GoBackButton::onClick(std::vector<BaseButton*> &CurrentButtons) {
    clearscreen();
    CurrentButtons = this->NextButtons;
    for(BaseButton* button: this->NextButtons){
        button->DrawButton();
    }
}

template <class N>
ModifyButton<N>::ModifyButton(const int x, const int y, const int width, const int height, const std::string text,
                              N *object):
                              BaseButton(x,y,width,height,text){
    this->object = object;
}

template <class N>
N * ModifyButton<N>::getObject() {
    return this->object;
}

template<class N>
void ModifyButton<N>::onClick(std::vector<BaseButton *> &CurrentButtons) {
    return ;

}

template<class N>
DeleteButton<N>::DeleteButton(const int x, const int y, const int width, const int height,
                                       const std::string text, N* object, MenuButton<N>* Button):
                                       ModifyButton<N>(x,y,width,height,text,object){
    this->Button = Button;

}

template <class N>
void DeleteButton<N>::onClick(std::vector<BaseButton*> &CurrentButtons) {
    N* current_object = this->getObject();
    this->Button->EraseObject(this->getObject());

    std::vector<BaseButton*>::iterator find_delete = std::find(CurrentButtons.begin(),CurrentButtons.end(),this);
    CurrentButtons.erase(find_delete);
    std::vector<BaseButton*>::iterator find_edit = std::find_if(CurrentButtons.begin(),CurrentButtons.end(),
                    [&current_object](BaseButton* button){
                        if(ModifyButton<N>* ModifyButton = dynamic_cast<::ModifyButton<N>*>(button)){
                            return ModifyButton->getObject() == current_object;
                        }else{
                            return false;
                        }

    }
    );
    if constexpr (std::is_same_v<N,Client>){
        std::vector<BaseButton*>::iterator find_reservation = std::find_if(CurrentButtons.begin(),CurrentButtons.end(),
                    [&current_object](BaseButton* button){
                        if(ModifyButton<N>* ModifyButton = dynamic_cast<::ModifyButton<N>*>(button)){
                            return ModifyButton->getObject() == current_object;
                        }else{
                            return false;
                        }
                    }
        );
        CurrentButtons.erase(find_reservation);
    }
    CurrentButtons.erase(find_edit);
    this->Button->onClick(CurrentButtons);

}


void BaseButton::DrawButton(){
    gotoxy(this->x,this->y);
    std::string str(this->width,'-');
    if(this->height > 0) std::cout << str;
    for(int i = 1; i < this->height; i++){
        gotoxy(this->x,this->y + i);
        std::cout << "|";
        gotoxy(this->x + this->width, this->y + i);
        std::cout << "|";
    }
    gotoxy((this->x + this->width/2) - this->text.length()/2, this->y + this->height/2);
    std::cout << this->text;
    gotoxy(this->x,this->y + this->height);
    if(this->height > 0) std::cout << str;
}


template <class N>
EditButton<N>::EditButton(const int x, const int y, const int width, const int height, const std::string text,
                                   N * object,BaseButton* button):ModifyButton<N>(x,y,width,height,text,object) {
    this->OriginalButton = button;
};
template <class N>
void EditButton<N>::onClick(std::vector<BaseButton*> &CurrentButtons) {
    clearscreen();
    std::string edit;
    this->getObject()->edit();
    this->OriginalButton->onClick(CurrentButtons);

}

template<class Client>
ShowReservation<Client>::ShowReservation(const int x, const int y, const int width, const int height, const std::string text,
                                    Client *object, MenuButton<Client> *button):
                                    ModifyButton<Client>(x,y,width,height,text,object){
    this->Button = button;
}

template <class Client>
void ShowReservation<Client>::onClick(std::vector<BaseButton *> &CurrentButtons) {
    clearscreen();
    std::vector<Reservation*> clientReservations = this->getObject()->getHistory();
    gotoxy(1,1);
    std::cout << "Reservations for " << this->getObject()->getName();
    gotoxy(1,3);
    int increment_y = 0;
    std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation Id" << std::setw(20) << "Reservation Size"
    << std::setw(8) << "CheckIn Date" << std::setw(8) << "Check Out Date" << std::setw(8) << "Room Id";
    for(Reservation* reservation: clientReservations){
        gotoxy(1,5 + increment_y);
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << reservation->getreservationNumber()
        << std::setw(20) << reservation->getReservationSize()
                  << std::setw(8) << reservation->getCheckIn() << std::setw(8) <<
                  reservation->getCheckOut() << std::setw(8) << reservation->getRoomId();
    }

}

template <typename N>
MenuButton<N>::MenuButton(const int x, const int y, const int width, const int height,
                          const std::string& text, const int currentPage,
                          std::vector<N *> &menu_items):
        BaseButton(x,y,width,height,text){
    this->menu_items = menu_items;
    this->CurrentPage = currentPage;

}

template <typename N>
void MenuButton<N>::onClick(std::vector<BaseButton*> &CurrentButtons) {
    clearscreen();
    int edit_delete_x;
    gotoxy(1,1);
    if constexpr(std::is_same_v<N,Client>){
        edit_delete_x = 60;
        std::cout << "CLIENTS: ";
        gotoxy(3,3);
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Name" << std::setw(10) << "NIF" << std::endl;
    }
    else if constexpr (std::is_same_v<N,Room>){
        edit_delete_x = 60;
        std::cout << "ROOMS: ";
        gotoxy(3,3);
        std::cout << std::left <<  std::setw(10) << std::setfill(' ') << "Room Id" << std::setw(15)
        << "Room Number" << std::setw(8)<< "Floor" << std::setw(10) << "Capacity" << std::setw(18)
        << "Price Per Night" << std::endl;

    }
    else if constexpr (std::is_same_v<N,Staff>){
        edit_delete_x = 110;
        std::cout << "STAFF: ";
        gotoxy(3,3);
        std::cout << std::left << std::setw(13) << "Type" <<  std::setw(20) << std::setfill(' ') << "Name" <<
        std::setw(10) << "NIF" << std::setw(7) << "Wage" << std::setw(19) << "Years Of Service"
        << std::setw(19) << "Floors Assigned" << std::setw(8) << "Shift" << std::setw(12) << "Evaluation";

    }
    BaseButton* InitialButton = new GoBackButton(85,0,10,2,"Go Back",CurrentButtons);
    CurrentButtons = {InitialButton};
    InitialButton->DrawButton();
    int increment_y = 0;
    for(N* item: this->menu_items){
        gotoxy(3,5 + increment_y);
        item->print();
        BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,4 + increment_y,8,0,"Edit",item,this);
        BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 5 + increment_y, 8,0,"Delete",item,this);
        if constexpr (std::is_same_v<N,Client>){
            BaseButton* ShowReservationButton = new ModifyButton<Client>(35,5 + increment_y,15,2,"Show Reservations",item);
            CurrentButtons.push_back(ShowReservationButton);
        }
        NewEditButton->DrawButton();
        NewDeleteButton->DrawButton();
        CurrentButtons.push_back(NewDeleteButton);
        CurrentButtons.push_back(NewEditButton);
        increment_y += 3;
    }
}

template <class N>
void MenuButton<N>::EraseObject(N * item) {
    typename std::vector<N *>::iterator find = std::find(this->menu_items.begin(),this->menu_items.end(),item);
    this->menu_items.erase(find);
}

bool ButtonWasPressed(BaseButton *button, INPUT_RECORD &Input_Record){
    if ( (Input_Record.Event.MouseEvent.dwMousePosition.X >= button->getX() &&
            Input_Record.Event.MouseEvent.dwMousePosition.X <= button->getX() + button->getWidth()) &&
            ( Input_Record.Event.MouseEvent.dwMousePosition.Y >= button->getY() &&
            Input_Record.Event.MouseEvent.dwMousePosition.Y <= button->getY() + button->getHeight()) ){
                    return true;
                        
         }
    return false;
}

void Authentication(Hotel* hotel){
    unsigned wait_new_attempt = 2000;
    std::string passwordAttempt = "";
    std::string name = "";
    while(!hotel->logIn(name,passwordAttempt)){
        std::cout << "Please write your name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "Please write your password: ";
        std::getline(std::cin,passwordAttempt);
        if(!hotel->logIn(name,passwordAttempt)){
            std::cout << std::endl;
            std::cout << "It seems you typed the wrong password. Please try again shortly!" << std::endl;
            Sleep(wait_new_attempt);
        }
        clearscreen();
    }

    std::cout << "Log In Was Successful! WELCOME" << std::endl;
    clearscreen();
}

template class MenuButton<Client>;
template class MenuButton<Staff>;
template class MenuButton<Room>;
