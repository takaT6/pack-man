/***
    PACKMAN.c
    g1954525 Takagaki Taichi

    プレヤーはパックマンを操作し、敵を避けるゲーム。
    敵は半径１００以内に近づくとプレーヤーを追う。
    操作はwで上、sで下、dで右、aで左
***/
#include <stdio.h>
#include <stdlib.h>
#include <handy.h>
int main (){
    hgevent *key;
    int px,py;//パックマンの位置座標
    int pvx,pvy;//パックマンの移動
    int a0,a1;//口の角度
    a0=10,a1=-10;//パックマンの初期  
    px=250,py=250;//パックマンの初期位置  
    int ex[5],ey[5],er[5],evx[5],evy[5];//敵4体ののx、y座標、半径、速度
    int i;//forのカウント
    ex[1]=100,ey[1]=100,er[1]=10,evx[1]=4,evy[1]=3;
    ex[2]=400,ey[2]=400,er[2]=10,evx[2]=-5,evy[2]=-4;
    ex[3]=100,ey[3]=400,er[3]=10,evx[3]=4,evy[3]=-3;
    ex[4]=400,ey[4]=100,er[4]=10,evx[4]=-3,evy[4]=4;
    HgOpen(500,500);
    HgSetFont(HG_T, 30);
    //スタート画面を表示
    HgText(30,270,"PUT THE KEY: w OR s OR d OR a");
    HgGetChar();
    HgClear();
    HgSetFillColor(HG_BLACK);
    HgBoxFill(0,0,600,600,0);
    //レイヤーの追加
    int lay1;
    lay1 = HgWAddLayer(0);
//メインプログラム
  for(;;){
        //パックマンを操作する
        HgWSetEventMask(lay1,HG_KEY_DOWN);
        key= HgEventNonBlocking();
        if(key!=NULL){
            switch(key->ch){
                case 'w':
                    pvx=0;
                    pvy=8;
                    a0=-350;
                    a1=70;              
                    break;
                case 's':
                    pvx=0;
                    pvy=-8;
                    a0=-70;
                    a1=350;
                    break;  
                case 'd':
                    pvx=8;
                    pvy=0;
                    a0=170;
                    a1=-170;
                    break;
                case 'a':
                    pvx=-8;
                    pvy=0;
                    a0=10;
                    a1=-10;
                    break;  
            }
        }
    //パックマンの位置
        px=px+pvx;
        py=py+pvy;
        HgLClear(lay1);
    //パックマンを描く
        HgWSetFillColor(lay1,HG_YELLOW);
        HgWFanFill(lay1,px,py,17,a0,a1,1);
    //パックマンと敵の距離
        int zx[5],zy[5];
        for(i=0;i<5;i++){
            zx[i]=ex[i]-px;
            zy[i]=ey[i]-py;
        }
//パックマンと敵の距離が１００以下になると追いかける
        if(abs(zx[1])<100 && abs(zy[1])<100){
            if(zx[1]>0){
                evx[1]=-4;
            }
            if(zy[2]>0){
                evy[1]=-5;
            }
            if(zx[1]<0){
                evx[1]=6;
            }
            if(zy[1]<0){
                evy[1]=4;
            }
        }
        if(abs(zx[2])<100 && abs(zy[2])<100){
            if(zx[2]>0){
                evx[2]=-6;
            }
            if(zy[2]>0){
                evy[2]=-5;
            }
            if(zx[2]<0){
                evx[2]=4;
            }
            if(zy[2]<0){
                evy[2]=5;
            }
        }
        if(abs(zx[3])<100 && abs(zy[3])<100){
            if(zx[3]>0){
                evx[3]=-5;
            }
            if(zy[3]>0){
                evy[3]=-4;
            }
            if(zx[3]<0){
                evx[3]=5;
            }
            if(zy[3]<0){
                evy[3]=6;
            }
        }
        if(abs(zx[4])<100 && abs(zy[4])<100){
            if(zx[4]>0){
                evx[4]=-6;
            }
            if(zy[4]>0){
                evy[4]=-4;
            }
            if(zx[4]<0){
                evx[4]=5;
            }
            if(zy[4]<0){
                evy[4]=5;
            }
        }
//敵の位置
        for(i=0;i<5;i++){
            ex[i]=ex[i]+evx[i];
            ey[i]=ey[i]+evy[i];
        }
//敵を４つ表示する
        HgWSetFillColor(lay1,HG_RED);
        HgWCircleFill(lay1,ex[1], ey[1], er[1],0);
        HgWSetFillColor(lay1,HG_BLUE);
        HgWCircleFill(lay1,ex[2], ey[2], er[2],0);
        HgWSetFillColor(lay1,HG_GREEN);
        HgWCircleFill(lay1,ex[3], ey[3], er[3],0);
        HgWSetFillColor(lay1,HG_ORANGE);
        HgWCircleFill(lay1,ex[4], ey[4], er[4],0);
        HgSleep(0.04);
//端っこに達したら逆に移動する
        //敵の場合
        for(i=0;i<5;i++){
            if(ex[i]>500){
                ex[i]=0;
            }
            if(ex[i]<0){
                ex[i]=500;
            }
            if(ey[i]>500){
                ey[i]=0;
            }
            if(ey[i]<0){
                ey[i]=500;
            }
            if(ex[i]>500){
                ex[i]=0;
            }
        }
        //パックマンの場合
        if(px>500){
            px=0;
        }
        if(px<0){
            px=500;
        }
        if(py>500){
            py=0;
        }
        if(py<0){
            py=500;
        }
        //パックマンと敵が接触したらゲームオーバー
        if(abs(zx[1])<25 && abs(zy[1])<25){//absは絶対値を計算する関数
            break;
        }
        if(abs(zx[2])<25 && abs(zy[2])<25){
            break;
        }
        if(abs(zx[3])<25 && abs(zy[3])<25){
            break;
        }
        if(abs(zx[4])<25 && abs(zy[4])<25){
            break;
        }
    }
//ゲームオーバーを表示する
    for(;;){
        HgSetColor(HG_YELLOW);
        HgSetFont(HG_T, 30);
        HgText(30,270,"GAME OVER !!!");
    }
}