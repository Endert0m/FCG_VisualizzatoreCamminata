#include <SFML/Graphics.hpp>
#include <math.h>
#include "pieces/headers/piece_interface.hpp"
#include "joints/headers/joint_interface.hpp"

template <typename T1, typename T2>
double dist(sf::Vector2<T1> p1, sf::Vector2<T2> p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


////////////////////////////////////////////////////////////
/// GUI state

struct State
{
    sf::RenderWindow window;
    int menubar_height = 50;
    std::vector<PieceInterface*> pieces;
    std::vector<JointInterface*> joints;
    sf::Vector2f cameraOffset = {0.,0.};

    sf::Clock clock;
    ReferencePlane selectedPlane = ReferencePlane::XZ;

    int selected = -1;

    bool rot_Piece = false;
    bool drag_Piece = false;
    bool drag = false;
    sf::Vector2i mouse_pos;

    State(unsigned w, unsigned h, std::string title) 
    {
        window = sf::RenderWindow(sf::VideoMode({w, h}), title);
        clock.restart();
    }
    void update();
};

///
////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
/// Fisics functions

void State::update(){
    

    for(PieceInterface* p : pieces){
        //p->update(clock);
    }
    for(JointInterface* j : joints){
        j->movechild();
    }
}

///
//////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Callback functions
void handle(const sf::Event::Closed &, State &gs)
{
    gs.window.close();
}

void handle(const sf::Event::TextEntered &textEnter, State &gs)
{
   
}

void handle(const sf::Event::KeyPressed &keyPressed, State &gs)
{
    if (keyPressed.scancode == sf::Keyboard::Scancode::Space){
        if (gs.selectedPlane == ReferencePlane::XZ)
            gs.selectedPlane = ReferencePlane::YZ;
        else 
            gs.selectedPlane = ReferencePlane::XZ;
    }
}

void handle(const sf::Event::MouseMoved &mouseMoved, State &gs)
{
    sf::Vector2i offset = mouseMoved.position - gs.mouse_pos;
    gs.mouse_pos = mouseMoved.position;
    float px = 1;
    float py = 0;
    switch (gs.selectedPlane)
    {
    case ReferencePlane::XZ:
        px = 1;
        py = 0;
        break;
    case ReferencePlane::YZ:
        px = 0;
        py = 1;
        break;
    
    default:
        break;
    }

    if (gs.drag){
        for(PieceInterface* p : gs.pieces){
            p->globalPos = {p->globalPos[0] + (offset.x * px), p->globalPos[1]+ (offset.x * py),p->globalPos[2] + offset.y};
        }
    }
    if (gs.selected != -1 && gs.drag_Piece){
        rb::Vector3 tmp = gs.pieces[gs.selected]->body.getPos();
        gs.pieces[gs.selected]->body.setPos({tmp[0]+ (offset.x * px),tmp[1]+ (offset.x * py),tmp[2]+offset.y});
    }
    if (gs.selected != -1 && gs.rot_Piece){
        rb::Vector3_s tmp = gs.pieces[gs.selected]->body.getRot();

        _Float16 nrot = _Float16(offset.x)/100;
        gs.pieces[gs.selected]->body.setRot({tmp[0]+(nrot*_Float16(py)),tmp[1]+(nrot*_Float16(px)),tmp[2]});
        
        //printf("Rotation : %f,%f,%f \n",gs.pieces[gs.selected]->body.getRot()[0],gs.pieces[gs.selected]->body.getRot()[1],gs.pieces[gs.selected]->body.getRot()[2]);
    }

    
}

void handle(const sf::Event::MouseButtonPressed &mouseBP, State &gs)
{
    gs.mouse_pos = mouseBP.position;
    if ( mouseBP.button == sf::Mouse::Button::Middle) gs.drag = true;
    if ( mouseBP.button == sf::Mouse::Button::Left){
        gs.drag_Piece = true;
        int i = 0;
        for (PieceInterface* p : gs.pieces){
            sf::Vector2f pos;
            if (gs.selectedPlane == ReferencePlane::XZ)
             pos = {p->globalPos[0]+ p->body.getPos()[0], p->globalPos[2]+ p->body.getPos()[2]};
            else if (gs.selectedPlane == ReferencePlane::YZ)
             pos = {p->globalPos[1]+ p->body.getPos()[1], p->globalPos[2]+ p->body.getPos()[2]};

            if (dist(pos,mouseBP.position) < 20){
                gs.selected = i;
            }
            i++;
        }
    }
    if ( mouseBP.button == sf::Mouse::Button::Right){
        gs.rot_Piece = true;
        int i = 0;
        for (PieceInterface* p : gs.pieces){
            sf::Vector2f pos;
            if (gs.selectedPlane == ReferencePlane::XZ)
            pos = {p->globalPos[0]+ p->body.getPos()[0], p->globalPos[2]+ p->body.getPos()[2]};
            else if (gs.selectedPlane == ReferencePlane::YZ)
            pos = {p->globalPos[1]+ p->body.getPos()[1], p->globalPos[2]+ p->body.getPos()[2]};

            if (dist(pos,mouseBP.position) < 20){
                gs.selected = i;
            }
            i++;
        }
    }

}

void handle(const sf::Event::MouseButtonReleased &, State &gs)
{
    gs.drag = false;
    gs.drag_Piece = false;
    gs.rot_Piece = false;
    gs.selected = -1;
}

void handle(const sf::Event::Resized &resized, State &gs)
{
    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized.size));
    gs.window.setView(sf::View(visibleArea));
}

template <typename T>
void handle(const T &, State &gs)
{
    // All unhandled events will end up here
}
///
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// Graphics
void doGUI(State &gs)
{
    // TODO: here code to display the menus
    //Bottoni
    
}

void doGraphics(State &gs)
{
    gs.window.clear();
    doGUI(gs);

    for(PieceInterface* p: gs.pieces){
        gs.window.draw(*p->draw(gs.selectedPlane));
    }
    
    // TODO: add here code to display shapes in your canvas

    gs.window.display();
}
///
////////////////////////////////////////////////////////////
