#include <SFML/Graphics.hpp>
#include <math.h>
#include "pieces/headers/piece_interface.hpp"
#include "joints/headers/joint_interface.hpp"
#include "collections/headers/collection_interface.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

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
    std::vector<CollectionInterface*> collections;

    std::vector<collection> createdColl;

    sf::Vector2f cameraOffset = {0.,0.};

    sf::Clock clock;
    float* tMul; 
    sf::Clock PieceClock;
    ReferencePlane selectedPlane = ReferencePlane::XZ;

    PieceInterface* selected = nullptr;
    bool rot_Piece = false;
    bool drag_Piece = false;
    bool drag = false;
    sf::Vector2i mouse_pos;

    /// per settare l'ntervallo di visualizzazione
    unsigned int* pos ;
    unsigned int* intervalMajLimit ;
    unsigned int* intervalMinLimit ;
    unsigned int maxEntries = 1000;
    bool play = true;

    State(unsigned w, unsigned h, std::string title, unsigned int* maj, unsigned int* min, unsigned int* pos) 
    {
        window = sf::RenderWindow(sf::VideoMode({w, h}), title);
        if (ImGui::SFML::Init(window)); // L'if è solo per togliere il warning, va aggiustato gestendo le eccezioni
        clock.restart();
        tMul = new float(1.0);
        PieceClock.restart();
        intervalMajLimit = maj;
        intervalMinLimit = min;
        this->pos = pos; 
        updateCollections();
    }
    void update();
    void setIntervall(int n){
        maxEntries = n;
    }

    void updateCollections(){
        createdColl.clear();
        for (auto c: collections){
            createdColl.push_back(c->create(selectedPlane));
        }
    }
    ~State(){
        delete tMul;
    }
};

///
////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
/// Fisics functions

void State::update(){

    /*
    std::vector<PieceInterface*> collPieces;
    std::vector<JointInterface*> collJoints;
    */
    if (play){
        for (auto i : collections){
            i->update(PieceClock, *tMul);
        }
    }

    for (auto i : createdColl){
        if (play){
            for (auto j : i.pieces){
                j->update(PieceClock, *tMul);
            }
        }
        for (auto j : i.joints){
            j->movechild();
        }
    }

    if (play){
        for(PieceInterface* p : pieces){
            p->update(PieceClock, *tMul);
        }
    }
    for(JointInterface* j : joints){
        j->movechild();
    }
    
}

///
//////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Callback functions
void handle_close(State &gs)
{
    gs.window.close();
}

void handle_text(const sf::Event::TextEntered &textEnter, State &gs)
{
   
}

void handle_keyPressed(const sf::Event::KeyPressed &keyPressed, State &gs)
{
    if (keyPressed.scancode == sf::Keyboard::Scancode::Space){
        if (gs.selectedPlane == ReferencePlane::XZ)
            gs.selectedPlane = ReferencePlane::YZ;
        else 
            gs.selectedPlane = ReferencePlane::XZ;
    }
    gs.updateCollections();
}


void handle_mouseMove(const sf::Event::MouseMoved &mouseMoved, State &gs)
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
        for(collection c : gs.createdColl){
            for(auto p : c.pieces){
                p->globalPos = {p->globalPos[0] + (offset.x * px), p->globalPos[1]+ (offset.x * py),p->globalPos[2] + offset.y};
            }
        }
    }

    #ifdef DEBUG_MODE

    if (gs.selected != nullptr && gs.drag_Piece){
        rb::Vector3 tmp = gs.selected->body.getPos();
        gs.selected->body.setPos({tmp[0]+ (offset.x * px),tmp[1]+ (offset.x * py),tmp[2]+offset.y});
    }
    if (gs.selected != nullptr && gs.rot_Piece){
        rb::Vector3 tmp = gs.selected->body.getRot();

        float nrot = float(offset.x)/100;
        gs.selected->body.setRot({tmp[0]+(nrot*py),tmp[1]+(nrot*px),tmp[2]});
        
        //printf("Rotation : %f,%f,%f \n",gs.pieces[gs.selected]->body.getRot()[0],gs.pieces[gs.selected]->body.getRot()[1],gs.pieces[gs.selected]->body.getRot()[2]);
    }
    #endif
    
}

void handle_mousePressed(const sf::Event::MouseButtonPressed &mouseBP, State &gs)
{
    gs.mouse_pos = mouseBP.position;
    if ( mouseBP.button == sf::Mouse::Button::Middle) gs.drag = true;

    #ifdef DEBUG_MODE

    if ( mouseBP.button == sf::Mouse::Button::Left){
        gs.drag_Piece = true;

        for (PieceInterface* p : gs.pieces){
            sf::Vector2f pos;
            if (gs.selectedPlane == ReferencePlane::XZ)
             pos = {p->globalPos[0]+ p->body.getPos()[0], p->globalPos[2]+ p->body.getPos()[2]};
            else if (gs.selectedPlane == ReferencePlane::YZ)
             pos = {p->globalPos[1]+ p->body.getPos()[1], p->globalPos[2]+ p->body.getPos()[2]};

            if (dist(pos,mouseBP.position) < 20){
                gs.selected = p;
            }
        }
        for (collection c : gs.createdColl){
            for (auto p : c.pieces){
                sf::Vector2f pos;
                if (gs.selectedPlane == ReferencePlane::XZ)
                pos = {p->globalPos[0]+ p->body.getPos()[0], p->globalPos[2]+ p->body.getPos()[2]};
                else if (gs.selectedPlane == ReferencePlane::YZ)
                pos = {p->globalPos[1]+ p->body.getPos()[1], p->globalPos[2]+ p->body.getPos()[2]};

                if (dist(pos,mouseBP.position) < 20){
                    gs.selected = p;
                }
                
            }
        }

    }
    if ( mouseBP.button == sf::Mouse::Button::Right){
        gs.rot_Piece = true;
        for (PieceInterface* p : gs.pieces){
            sf::Vector2f pos;
            if (gs.selectedPlane == ReferencePlane::XZ)
            pos = {p->globalPos[0]+ p->body.getPos()[0], p->globalPos[2]+ p->body.getPos()[2]};
            else if (gs.selectedPlane == ReferencePlane::YZ)
            pos = {p->globalPos[1]+ p->body.getPos()[1], p->globalPos[2]+ p->body.getPos()[2]};

            if (dist(pos,mouseBP.position) < 20){
                gs.selected = p;
            }
            
        }
        for (collection c : gs.createdColl){
            for (auto p : c.pieces){
                sf::Vector2f pos;
                if (gs.selectedPlane == ReferencePlane::XZ)
                pos = {p->globalPos[0]+ p->body.getPos()[0], p->globalPos[2]+ p->body.getPos()[2]};
                else if (gs.selectedPlane == ReferencePlane::YZ)
                pos = {p->globalPos[1]+ p->body.getPos()[1], p->globalPos[2]+ p->body.getPos()[2]};

                if (dist(pos,mouseBP.position) < 20){
                    gs.selected = p;
                }
                
            }
        }
    }
    
    #endif

}

void handle_mouseRelease(const sf::Event::MouseButtonReleased &, State &gs)
{
    gs.drag = false;
    gs.drag_Piece = false;
    gs.rot_Piece = false;
    gs.selected = nullptr;
}



void handle_resize(const sf::Event::Resized &resized, State &gs)
{
    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized.size));
    gs.window.setView(sf::View(visibleArea));
}


///
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// Graphics
void doGUI(State &gs)
{
    //Bottoni
    sf::Time elapsed = gs.clock.restart();

    unsigned int zero = 0;

    ImGui::SFML::Update(gs.window, elapsed);

    //Finestra gestione posizione nei dati
    ImGuiWindowFlags sdp_flags = ImGuiWindowFlags_NoMove|
                                 ImGuiWindowFlags_NoResize|
                                 ImGuiWindowFlags_NoScrollbar|
                                 ImGuiWindowFlags_NoCollapse|
                                 ImGuiWindowFlags_NoTitleBar;
   
    ImGui::Begin("Set data position", 0,sdp_flags);
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.3);
    ImGui::SliderScalar("Start", ImGuiDataType_U32 ,gs.intervalMinLimit,&zero,gs.intervalMajLimit);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.5);
    if (ImGui::SliderScalar("Pos", ImGuiDataType_U32 ,gs.pos,gs.intervalMinLimit,gs.intervalMajLimit)){
        gs.play = false;
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.8);
    ImGui::SliderScalar("End", ImGuiDataType_U32 ,gs.intervalMajLimit,gs.intervalMinLimit,&gs.maxEntries);
    bool red = false;
    if (!gs.play){
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1,0,0,1));
        red = true;
    }
    ImGui::SameLine();
    if (ImGui::ArrowButton("Play", ImGuiDir_Right)){
        gs.play = !gs.play;
    }
    if (red) ImGui::PopStyleColor();
    ImGui::End();


    //Finestra gestione piano visualizzazione
    ImGui::Begin("Set visualization plane",0,sdp_flags);
    const char* MyEnumNames[] = { "XZ", "YZ", "-XZ" };
    int currentPlane = (int)gs.selectedPlane;
    if (ImGui::SliderInt("Selected Plane", &currentPlane,0,2,MyEnumNames[currentPlane])){
        gs.selectedPlane = (ReferencePlane)currentPlane;
        gs.updateCollections();
    } 
    ImGui::End();

   
    //Finestra gestione velocità di riproduzione 
    ImGui::Begin("Set time multiplier", 0,sdp_flags);
    const float TimeMul[] = {0.5, 0.75, 1, 1.25, 1.5};
    const char* TimeMulChar[] = {"0.5", "0.75", "1", "1.25", "1.5"};
    static int Timeid = 2;
    ImGui::SliderInt("Time", &Timeid,0,4,TimeMulChar[Timeid]);
    *gs.tMul = TimeMul[Timeid]; 
    ImGui::End();

    //Finestra controllo sovrapposizione 
    
    


    sf::Vector2u wsize = gs.window.getSize();
    ImGui::SetWindowPos("Set data position",ImVec2(0,wsize.y - 30));
    ImGui::SetWindowSize("Set data position",ImVec2(wsize.x,30));
    ImGui::SetWindowPos("Set visualization plane",ImVec2(wsize.x-400,0));
    ImGui::SetWindowSize("Set visualization plane",ImVec2(400,30));
    ImGui::SetWindowPos("Set time multiplier",ImVec2(wsize.x-400,wsize.y - 60));
    ImGui::SetWindowSize("Set time multiplier",ImVec2(400,30));
    ImGui::SFML::Render(gs.window);
}

void doGraphics(State &gs)
{
   
    gs.window.clear();

    //disegno i pezzi singoli
    for(PieceInterface* p: gs.pieces){
        gs.window.draw(*p->draw(gs.selectedPlane));
    }
    
    //disegno le collezioni
    for(auto c : gs.createdColl){
        for(auto p : c.pieces){
            gs.window.draw(*p->draw(gs.selectedPlane));
        }
    }

    while (const std::optional event = gs.window.pollEvent()) {
        ImGui::SFML::ProcessEvent(gs.window, *event);
        if (event->is<sf::Event::Closed>())
            handle_close (gs);
        if (const auto* resized = event->getIf<sf::Event::Resized>())
            handle_resize (*resized, gs);
        if (const auto* pressed = event->getIf<sf::Event::KeyPressed>())
            handle_keyPressed (*pressed, gs);
        if (const auto* moved = event->getIf<sf::Event::MouseMoved>())
            handle_mouseMove (*moved, gs);   
        if (const auto* mpressed = event->getIf<sf::Event::MouseButtonPressed>())
            handle_mousePressed (*mpressed, gs); 
        if (const auto* mreleased = event->getIf<sf::Event::MouseButtonReleased>())
            handle_mouseRelease (*mreleased, gs);  
    }
    doGUI(gs);

  
    
    // TODO: add here code to display shapes in your canvas

    gs.window.display();
}
///
////////////////////////////////////////////////////////////
