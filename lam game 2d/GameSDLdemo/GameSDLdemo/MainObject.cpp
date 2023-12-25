#include"MainObject.h"
#include"ThreatsObject.h"

MainObject::MainObject()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_MAIN_OBJECT;
    rect_.h = HEIGHT_MAIN_OBJECT;
    x_val_  = 0;
    y_val   = 0;

}

MainObject::~MainObject()
{
    ;
}

void MainObject::HandleInputAction(SDL_Event events)

{
    if(events.type == SDL_KEYDOWN)    // su ly di chuyen nhan vat
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
             y_val -=HEIGHT_MAIN_OBJECT/4;
             break;
        case SDLK_DOWN:
             y_val +=HEIGHT_MAIN_OBJECT/4;
             break;
        case SDLK_RIGHT:
             x_val_ += WIDTH_MAIN_OBJECT/4;
             break;
        case SDLK_LEFT:
             x_val_ -= WIDTH_MAIN_OBJECT/4;
             break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_UP :  y_val += HEIGHT_MAIN_OBJECT/4;break; //len xuong tung buoc nhan vat
        case SDLK_DOWN :y_val -= HEIGHT_MAIN_OBJECT/4;break;
        case SDLK_LEFT :x_val_ += HEIGHT_MAIN_OBJECT/4;break;
        case SDLK_RIGHT :x_val_ -=HEIGHT_MAIN_OBJECT/4;break;

        }
    }
    else if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        AmoObject*p_amo = new AmoObject();
        if(events.button.button == SDL_BUTTON_LEFT) // su ly dan ban nhap chuot trai;
        {
            p_amo->SetWidthHeight(WIDTH_LASER,HEIGHT_LASER);
            p_amo->LoadImg("laser.png");
            p_amo->set_type(AmoObject::LASER);
        }
        else if (events.button.button == SDL_BUTTON_RIGHT) // su ly dan ban nhap chuot phai ;
        {
            p_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
            p_amo->LoadImg("sphere.png");
            p_amo->set_type(AmoObject::SPHERE);

        }
            p_amo->SetRect(this->rect_.x + this->rect_.w - 40, this->rect_.y + this -> rect_.h * 0.8);//  chinh sua dan ban ra
            p_amo->set_is_move(true);
            p_amo->set_x_val(20);
            p_amo_list_.push_back(p_amo);
    }
    else if (events.type == SDL_MOUSEBUTTONUP)
    {
           
    }
    else
    {
        ;//
    }

}

void MainObject::MakeAmo(SDL_Surface* des)
{
    for(int i = 0 ; i < p_amo_list_.size(); i++)

    {
     
        AmoObject* p_amo = p_amo_list_.at(i);
        if(p_amo != NULL)
        {
            if(p_amo->get_is_move())
            {
                p_amo->Show(des);
                p_amo->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT);
            }
            else
            {
                if(p_amo != NULL)
                {
                    p_amo_list_.erase(p_amo_list_.begin() + i);
                    delete p_amo;
                    p_amo = NULL;
                }
            }
        }
    }
}


void MainObject::HandleMove()
{
      rect_.x += x_val_;
        
      if(rect_.x < 0  ||  rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
      {
          rect_.x -= x_val_;
      }


      rect_.y += y_val;
       if(rect_.y < 0  ||  rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
      {
          rect_.y -= y_val;
      }


}

void MainObject::RemoveAmo(const int& idx)
{
    
    
    for(int i = 0 ; i < p_amo_list_.size(); i++)
    {
        if(idx < p_amo_list_.size())
        {
        AmoObject* p_amo = p_amo_list_.at(idx);
        p_amo_list_.erase(p_amo_list_.begin() + idx);
        if(p_amo != NULL)
        {
            delete p_amo;
            p_amo = NULL;
        }
      }
   }
}