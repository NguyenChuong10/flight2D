#include"Common_Function.h"
#include"MainObject.h"
#include"ThreatsObject.h"

// Ctrl R + Ctrl W de hien an hien may cai dau ... 1 . dai dien cho 1 space 

bool Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }
  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if (g_screen == NULL)
  {
    return false;
  }
  return true;
}



 
int main(int arc, char* argv[])
{
  int bkgn_x = 0;
  bool is_run_screen = true;

  bool is_quit = false;
  if (Init() == false)
   return 0;
 
  g_bkground =SDLCommonFunc:: LoadImage("bk9.png");
  if (g_bkground == NULL)
  {
    return 0;
  }
 
  
  // load ảnh   nhân vật chính 
 MainObject human_object;
 human_object.SetRect(100,200);
 bool ret = human_object.LoadImg("plane_fly.png");
     if(!ret)
     {
         return 0;
     }

     

     //tạo nhân vật đe doạ

     ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
     for(int t = 0 ; t <NUM_THREATS;t++ )
{
         ThreatObject* p_threat = (p_threats + t);
         if(p_threat != NULL)
         {
         ret = p_threat->LoadImg("af1.png");
         if(ret == false)
         {
                 return 0;
         }

        int rand_y = rand()%400;
        if(rand_y > SCREEN_HEIGHT -200)
        {
            rand_y = SCREEN_HEIGHT*0.3;
        }

        p_threat->SetRect(SCREEN_WIDTH +t*400  ,rand_y);
        p_threat->set_x_val(3);

        AmoObject* p_amo = new AmoObject();

        p_threat->InitAmo(p_amo);
         }
}
 
     //tạo màn hình chạy liên tục ko tắt
    
  while (!is_quit) 
  {
    while (SDL_PollEvent(&g_even)) 
    {
      if (g_even.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
      human_object.HandleInputAction(g_even);
    }


    // chạy ảnh dài
    if(is_run_screen ==true)
    {
         bkgn_x -= 2;
         if(bkgn_x <= -(WIDTH_BACKGROUND-SCREEN_WIDTH))
             {
                 is_run_screen = false;
             }
         else
             {
              SDLCommonFunc::ApplySurface(g_bkground,g_screen,bkgn_x,0);
             }
    }
    else
    {
        SDLCommonFunc::ApplySurface(g_bkground,g_screen,bkgn_x, 0);

    }
    // tải background  ,chuyen dong , dan ban
    human_object.HandleMove();
    human_object.Show(g_screen);
    human_object.MakeAmo(g_screen);




    // chay doi tuong de doa
    for(int tt = 0 ; tt < NUM_THREATS; tt++)
    {    
        ThreatObject* p_threat = (p_threats +tt);
        if(p_threat != NULL)
        {
         p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
         p_threat->Show(g_screen);
         p_threat->MakeAmo(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);

         if ( SDL_Flip(g_screen) == -1)
         return 0;



         //kiem tra va cham cua nhan vat chinh va nhan vat de doa.

         bool is_col = SDLCommonFunc::CheckCollision(human_object.GetRect(),p_threat->GetRect());
         if(is_col)
         {
             if(MessageBox(NULL,L"GAME OVER",L"InfO",MB_OK)==IDOK)
             { 
                delete[] p_threats;
                SDLCommonFunc:: CleanUp();
                SDL_Quit();
                return 1;
             }
         }
         std::vector<AmoObject*> amo_list = human_object.GetAmoList();
         for(int im = 0 ; im <amo_list.size(); im++)
         {
             AmoObject*p_amo = amo_list.at(im);
             if(p_amo != NULL)
             {
                 bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(),p_threat->GetRect());
                 if(ret_col)
                 {
                     p_threat->Reset(SCREEN_WIDTH +tt*400);
                     human_object.RemoveAmo(im);

                 }

             }
         }
    }
}
   
    // CAP NHAT LIEN TUC MAN HINH
    if ( SDL_Flip(g_screen) == -1)
    return 0;
  }

  delete[] p_threats;
  SDLCommonFunc:: CleanUp();
  SDL_Quit();
  return 1;
}



