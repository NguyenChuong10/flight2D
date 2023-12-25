#include"ThreatsObject.h"

ThreatObject::ThreatObject()
{
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT*0.5;
    rect_.w = WIDTH_THREAT;
    rect_.h = HEIGHT_THREAT;

    x_val_ = 0;
    y_val_ = 0;

}
ThreatObject::~ThreatObject()

{
    if(p_amo_list_.size() > 0)
    {
        for(int i = 0 ; i < p_amo_list_.size();i++)
        {
            AmoObject* p_amo = p_amo_list_.at(i);
            if(p_amo != NULL)
            {
                delete p_amo;
                p_amo = NULL;
            }
        }
        p_amo_list_.clear();
    }
}

void ThreatObject::InitAmo(AmoObject*p_amo)
{
    
}


void ThreatObject::MakeAmo(SDL_Surface*des,const int&x_limit ,const int &y_limit)
{
    for(int i = 0 ; i<p_amo_list_.size();i++)
    {
        AmoObject* p_amo = p_amo_list_.at(i);
        if(p_amo)
        {
            if (p_amo->get_is_move())
            {
                p_amo->Show(des);
                p_amo->HandleMoveRightToLeft();
            }
            else
            {
                p_amo->set_is_move(true);
                p_amo->SetRect(rect_.x , rect_.y +rect_.h*0.5);
            }
        }
       
    }
}


void ThreatObject::HandleMove(const int& x_border,const int & y_border)
{
    rect_.x -= x_val_;
    if(rect_.x < 0)
    {
        rect_.x = SCREEN_WIDTH;
        int rand_y = rand()%400;
        if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
        {
            rand_y = SCREEN_HEIGHT*0.3;
        }
        rect_.y =  rand_y;
    }
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
    //Todo
}

void  ThreatObject::Reset(const int& xboder) // reeset dan ban cua nhan vat chinh
{
    rect_.x = xboder;
     rect_.x = SCREEN_WIDTH;
        int rand_y = rand()%400;
        if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
        {
            rand_y = SCREEN_HEIGHT*0.3;
        }
        rect_.y =  rand_y;

        for(int i = 0 ; i <p_amo_list_.size();i++)
        {
            AmoObject* p_amo = p_amo_list_.at(i);
            if(p_amo)
            {
                ResetAmo(p_amo);
            }
      }
}

void ThreatObject::ResetAmo(AmoObject* p_amo)

{
     p_amo->SetRect(rect_.x,rect_.y + rect_.h*0.5);
}
