#include "draw.h"
#include<QPainter>
#include<QPaintEvent>
#include<QRect>
#include<QDebug>
#include<QEventLoop>
#include<QEvent>
#include<QTimer>
#include<QMessageBox>
#include <QMediaPlayer>


draw::draw(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);
}
void draw::set_need_wash()
{
    dirt_map map=dirt_times[all_states.size()-1];//最后一张图
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(map.map[j+1][i+1]>=2){
                Pos pos = pair<int,int>(j+1,i+1);
                need_wash.insert(pos);
            }
        }
    }
    wash_size=need_wash.size();
}

void draw::setcould_wash()
{
    could_wash.clear();
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(need_wash.contains(pair<int,int>(j+1,i+1))){
                if(!have_wash.contains(pair<int,int>(j+1,i+1))){
                    if(dirt_times[time].map[j+1][i+1]!=0){
                        could_wash.insert(pair<int,int>(j+1,i+1));
                    }
                }
            }
        }
    }
    for(auto it = have_wash.begin();it!=have_wash.end();it++){
        qDebug()<<it->first<<" "<<it->second<<endl;
    }
}
int draw::find_pos(int x, int y, QVector<state> state)
{
    int i=0;
    for(;i<state.size();i++){
        if(state[i].enable==true){
        if(state[i].x==x&&state[i].y==y){
            return i;
        }
        }
    }
    return -1;
}

bool draw::static_check()
{
    QVector<state> present=all_states[time];
    for(int i=0;i<present.size();i++){
        for(int j=i+1;j<present.size();j++){
            if(present[i].enable==true&&present[j].enable==true){
                if(dis(present[i].x,present[i].y,present[j].x,present[j].y)<=2){
                    QMessageBox m;
                    QString str = QString("静态约束错误，在(%1,%2)与(%3,%4)").arg(present[i].x)
                            .arg(present[i].y).arg(present[j].x).arg(present[j].y);
                    m.setText(str);
                    m.exec();
                    return false;
                }
            }
        }
    }
    return true;

}

bool draw::dynamic_check()
{
    if(time==0) return true;
    QVector<state> present=all_states[time];
    QVector<state> previous=all_states[time-1];
    for(int i=0;i<present.size();i++){
        for(int j=0;j<previous.size();j++){
            if(present[i].enable==true&&previous[j].enable==true&&present[j].enable==true){
                if(present[i].id!=previous[j].id){
                    if(dis(present[i].x,present[i].y,previous[j].x,previous[j].y)<=2){
                        QMessageBox m;
                        QString str = QString("动态约束错误，在(%1,%2)与(%3,%4)").arg(present[i].x)
                                .arg(present[i].y).arg(previous[j].x).arg(previous[j].y);
                        m.setText(str);
                        m.exec();
                        return false;
                }
            }
        }
    }
}
    return true;
}

bool draw::in_check(state s)
{
    int x=s.x;
    int y=s.y;
    bool ok=false;
    for(int i=0;i<in_r.size();i++){
        if(in_r[i]==0){
            if(x==1&&y==in_c[i]) {
                ok=true;
                break;
            }
        }
        else if(in_r[i]==c+1){
            if(x==c&&y==in_c[i]){
                ok=true;
                break;
            }
        }
        else if(in_c[i]==0){
            if(y==1&&x==in_r[i]){
                ok=true;
                break;
            }

        }
        else{
            if(y==r&&x==in_r[i]){
                ok=true;
                break;
            }
        }
    }
    return ok;
}

void draw::setblock()
{
    block.clear();
    QVector<state> tmp = all_states[time];
    for(int i=0;i<tmp.size();i++){
        if(tmp[i].enable==false) continue;
        int x=tmp[i].x;
        int y=tmp[i].y;
        block.insert(pair<int,int>(x,y));
        block.insert(pair<int,int>(x-1,y));
        block.insert(pair<int,int>(x+1,y));
        block.insert(pair<int,int>(x,y-1));
        block.insert(pair<int,int>(x,y+1));
        block.insert(pair<int,int>(x-1,y-1));
        block.insert(pair<int,int>(x-1,y+1));
        block.insert(pair<int,int>(x+1,y-1));
        block.insert(pair<int,int>(x+1,y+1));
    }
}
void draw::drawbackground(QPaintEvent *ev)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(3);
    p.setPen(pen);
    QVector<QRect> rects;
    //qDebug()<<r<<" "<<c<<endl;
    for(int i=0;i<r;i++){   //画背景方格
        for(int j=0;j<c;j++){
            QRect rect(j*50+150,i*50+150,50,50);
            rects.push_back(rect);
        }
    }
    p.drawRects(rects);
//画input
    p.setBrush(Qt::yellow);
    for(int i=0;i<in_number;i++){
        int x=in_r[i];
        int y=in_c[i];//获得坐标
        //qDebug()<<x<<" "<<y<<endl;
        if(x==0){//横的input
            QRect rect(50,100+y*50,100,50);
            p.drawRect(rect);
            p.drawText(rect, Qt::AlignCenter, tr("Input"));

        }
        else if(x==c+1){
            QRect rect(x*50+100,100+y*50,100,50);
            p.drawRect(rect);
            p.drawText(rect, Qt::AlignCenter, tr("Input"));
        }
        else if(y==0){
            QRect rect(x*50+100,50,50,100);
            p.drawRect(rect);
            p.drawText(rect, Qt::AlignCenter, tr("Input"));
        }
        else{
            QRect rect(x*50+100,y*50+100,50,100);
            p.drawRect(rect);
            p.drawText(rect, Qt::AlignCenter, tr("Input"));
        }
    }
    //画Output
    p.setBrush(Qt::cyan);
    if(out_x!=0||out_y!=0){
    if(out_x==0){
        QRect rect(50,100+out_y*50,100,50);
        p.drawRect(rect);
        p.drawText(rect, Qt::AlignCenter, tr("Output"));
    }
    else if(out_x==c+1){
        QRect rect(out_x*50+100,100+out_y*50,100,50);
        p.drawRect(rect);
        p.drawText(rect, Qt::AlignCenter, tr("Output"));
    }
    else if(out_y==0){
        QRect rect(out_x*50+100,50,50,100);
        p.drawRect(rect);
        p.drawText(rect, Qt::AlignCenter, tr("Out\nput"));
    }
    else{
        QRect rect(out_x*50+100,out_y*50+100,50,100);
        p.drawRect(rect);
        p.drawText(rect, Qt::AlignCenter, tr("Out\nput"));
    }
    }
    if(started&&washmode){
    p.setBrush(Qt::blue);
    QRect rect1(50,150,100,50);
    p.drawRect(rect1);
    p.drawText(rect1,Qt::AlignCenter, tr("Wash Input"));
    QRect rect2(c*50+150,r*50+100,100,50);
    p.setBrush(QColor(185,122,86));
    p.drawRect(rect2);
    p.drawText(rect2,Qt::AlignCenter, tr("Waste"));
    }
}

void draw::drawcircus(QPaintEvent *ev, int time)

{
    static QVector<QColor> color;
    color.push_back(QColor(224,11,244));color.push_back(QColor(11,244,221));
    color.push_back(QColor(63,72,204));color.push_back(QColor(255,174,200));
    color.push_back(QColor(255,127,19));color.push_back(QColor(185,122,86));
    color.push_back(QColor(236,28,36));color.push_back(QColor(14,209,69));
    //qDebug()<<all_states.size()-1<<"size!!!!"<<endl;
    if(time>all_states.size()-1) return;
    //qDebug()<<time<<"start!!!!"<<endl;
    QPainter p(this);
    QPen pen;
    pen.setWidth(0);
    p.setPen(pen);
    //p.setBrush(Qt::yellow);
    //qDebug()<<all_states.size()<<endl;
    QVector<state> tmp = all_states[time];

    for(int i=0;i<tmp.size();i++){

        state circus = tmp[i];
//        if(circus.io==1){
//            bool ok = in_check(circus);
//            if(ok){
//                circus.io=-1;
//                draw::error=false;
//            }
//            else{
//                QMessageBox m;m.setText("Input附近应有输入端口");
//                m.exec();
//                draw::time=0;
//                emit timechanged(draw::time);
//                draw::error=true;
//                return;
//            }
//        }
        if(circus.enable==false) continue;//不看消失的
        int x = circus.x;
        int y = circus.y;
        //qDebug()<<x<<" "<<y<<" posssss"<<endl;
        p.setBrush(color[circus.id%8]);
        if(circus.oval==true){//是个椭圆
            if(circus.horizon==true){//是个横着的椭圆
                p.drawEllipse(x*50+50,y*50+100,150,50);
                continue;
            }
            else{//是个竖着的椭圆
                p.drawEllipse(x*50+100,y*50+50,50,150);
            }
        }
        else{//是个正常的圆
            if(circus.normal==true){//小圆
                p.drawEllipse(x*50+100,y*50+100,50,50);
            }
            else{//大圆
                p.drawEllipse(x*50+95,y*50+95,60,60);
            }

        }
    }
    //qDebug()<<time<<"succeddddddd"<<endl;
}

void draw::drawtrace(QPaintEvent *ev, int time)
{

    static QVector<QColor> color;
    color.push_back(QColor(224,11,244));color.push_back(QColor(11,244,221));
    color.push_back(QColor(63,72,204));color.push_back(QColor(255,174,200));
    color.push_back(QColor(255,127,19));color.push_back(QColor(185,122,86));
    color.push_back(QColor(236,28,36));color.push_back(QColor(14,209,69));
    if(time>all_states.size()-1) return;
    QPainter p(this);

    QVector<state> tmp = all_states[time];
    for(int i=0;i<tmp.size();i++){

        state trace = tmp[i];
        QPen pen;
        pen.setWidth(3);
        pen.setBrush(color[trace.id%8]);
        p.setPen(pen);
        for(int j=0;j<trace.tr_x.size();j++){
            int x = trace.tr_x[j];
            int y = trace.tr_y[j];//痕迹的位置
            if(dirt_times[time].map[x][y]==0) continue;
            if(find_pos(x,y,tmp)!=-1){//说明路径上有点
                continue;
            }
            p.drawEllipse(x*50+105,y*50+105,40,40);
        }
    }
}

void draw::drawdirt(QPaintEvent *ev, int time)

{
//    if(time!=all_states.size()-1){
//        dirt=false;
//        QMessageBox m;m.setText("不是最后一步");
//                m.exec();

//        return;
//    }
    QPainter p(this);
    QVector<state> tmp = all_states[time];
    int map[100][100]={{}};
    for(int i=0;i<tmp.size();i++){//如果点是enable，则要加当前位置，否则不加当前位置
       // if(tmp[i].enable==true){
            //map[tmp[i].x][tmp[i].y]++;
//            for(int j=0;j<tmp[i].tr_x.size();j++){
//                map[tmp[i].tr_x[j]][tmp[i].tr_y[j]]++;
//            }
       QSet<QPair<int,int>> set;
       for(int j=0;j<tmp[i].tr_x.size();j++){
           QPair<int,int> pair = {tmp[i].tr_x[j],tmp[i].tr_y[j]};
           set.insert(pair);
        }
       for(auto it = set.begin();it!=set.end();it++){
           map[it->first][it->second]++;
       }
//        else{
//            for(int j=0;j<tmp[i].tr_x.size();j++){
//                map[tmp[i].tr_x[j]][tmp[i].tr_y[j]]++;
//            }
//        }
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            QRect rect(j*50+150,i*50+150,50,50);
            QString str=QString(dirt_times[time].map[j+1][i+1]);
            //qDebug()<<str<<endl;
            p.drawText(rect, Qt::AlignCenter, QString::number(map[j+1][i+1]));
        }
    }
}

void draw::drawwash(QPaintEvent *ev)

{
    if(wash.yes==false){ return;}
    QPainter p(this);
    QPen pen;
    p.setBrush(Qt::blue);
    p.setPen(pen);
    p.drawEllipse(wash.x*50+100,wash.y*50+100,50,50);

    if(dirt_times[time].map[wash.x][wash.y]!=0){
        for(int i=time;i<all_states.size();i++){
            dirt_times[i].map[wash.x][wash.y]--;
        }
    }
    //qDebug()<<wash.x<<" "<<wash.y<<"lalalalalla"<<endl;

    //qDebug()<<wash.x<<" "<<wash.y<<"hahhahahaha"<<endl;
}

void draw::drawblock(QPaintEvent *ev)
{
    for(auto it=mouseblock.begin();it!=mouseblock.end();it++){

        int x = it->first;
        int y = it->second;
        if(x>=1&&x<=c&&y>=1&&y<=r){
        QPainter p(this);
        p.setBrush(Qt::red);
        p.drawRect(x*50+100,y*50+100,50,50);
        update();}
    }
}
void draw::next()
{
    if(filed==false){
        QMessageBox m;m.setText("请先读入文件");
       m.exec();
    }
    if(time==all_states.size()-1){
        QMessageBox m;m.setText("已是最后一步");
        m.exec();

    }
    else{

        time++;
        update();
        playsound(time);
        emit timechanged(time);
        bool check1 = static_check();
        if(check1==false) {
            time--;
            emit timechanged(time);
            return;
        }
        bool check2 = dynamic_check();
        if(check2==false) {
            time--;
            emit timechanged(time);
            return;
        }
        //setcould_wash();
       // for(auto it = could_wash.begin();it!=could_wash.end();it++){
         //   qDebug()<<it->first<<" "<<it->second<<"could wash"<<endl;
        //}
    }

}

void draw::last()

{
    if(filed==false){
        QMessageBox m;m.setText("请先读入文件");
       m.exec();
    }
    if(time==0){
        QMessageBox m;m.setText("已是第一步");
        m.exec();
    }
    else{
        time--;
        playsound(time);
        update();
        emit timechanged(time);
        bool check1 = static_check();
        if(check1==false) {
            time++;
            emit timechanged(time);
            return;
        }
    }
}

void draw::reset()
{
    if(filed==false){
        QMessageBox m;m.setText("请先读入文件");
       m.exec();
    }
    time=0;
    emit timechanged(time);
    wash.yes=false;
    //need_wash.clear();
    have_wash.clear();
    could_wash.clear();
    dirt_times=dirt_times2;
    update();
}

void draw::setsound()
{
    for(int i=0;i<all_states.size();i++){
        Music tmp=NO;
        QVector<state> states = all_states[i];
        for(int j=0;j<states.size();j++){
            if(states[j].music==Splited){
                tmp=Splited;
                break;
            }
        }
        if(tmp==Splited){
            sound.push_back(tmp);
            continue;//如果有Splited就继续
        }
        for(int j=0;j<states.size();j++){
            if(states[j].music==Spliting){
                tmp=Spliting;
                break;
            }
        }
        if(tmp==Spliting){
            sound.push_back(tmp);
            continue;//如果有Splited就继续
        }
        for(int j=0;j<states.size();j++){
            if(states[j].music==Merged){
                tmp=Merged;
                break;
            }
        }
        if(tmp==Merged){
            sound.push_back(tmp);
            continue;//如果有Splited就继续
        }
        for(int j=0;j<states.size();j++){
            if(states[j].music==Move){
                tmp=Move;
                break;
            }
        }
        if(tmp==Move){
            sound.push_back(tmp);
            continue;//如果有Splited就继续
        }
        for(int j=0;j<states.size();j++){
            if(states[j].music==Mix){
                tmp=Mix;
                break;
            }
        }
        if(tmp==Mix){
            sound.push_back(tmp);
            continue;//如果有Splited就继续
        }
        sound.push_back(tmp);//此时没有音乐;
    }
    /*for(int i=0;i<sound.size();i++){
        qDebug()<<i<<" "<<sound[i]<<endl;
    }*/
}

void draw::playsound(int time)
{
    Music music = sound[time];
    QMediaPlayer* player = new QMediaPlayer(this);
    if(music==Move||music==Mix){
        player->setMedia(QUrl("qrc:/sound/move.wav"));
    }
    else if(music==Splited){

        player->setMedia(QUrl("qrc:/sound/splited.wav"));

    }
    else if(music==Spliting){
        player->setMedia(QUrl("qrc:/sound/spliting.wav"));
    }
    else if(music==Merged){
        player->setMedia(QUrl("qrc:/sound/merge.wav"));
    }
    else{
        player->setVolume(0);
        return;
    }
    player->setVolume(30);
    player->play();
}


void draw::con_draw()
{
    if(filed==false){
        QMessageBox m;m.setText("请先读入文件");
       m.exec();
    }
    //time=0;
    //emit timechanged(time);
    update();
    while(time<=all_states.size()-2){//0.5s换一次
        QEventLoop el;
        QTimer::singleShot(500,&el,SLOT(quit()));
        el.exec();
        time++;
        playsound(time);
        //qDebug()<<time<<"lallallala"<<endl;
        //if(time>all_states.size()-1) break;
        bool check1 = static_check();
        if(check1==false) {
            emit timechanged(time);
            time--;
            emit timechanged(time);
            return;
        }
        bool check2 = dynamic_check();
        if(check2==false) {
            emit timechanged(time);
            time--;
            emit timechanged(time);
            return;
        }
        emit timechanged(time);
        update();
    }
    bool check1 = static_check();
    if(check1==false) {
        emit timechanged(time);
        time--;
        emit timechanged(time);
        return;
    }
    bool check2 = dynamic_check();
    if(check2==false) {
        emit timechanged(time);
        time--;
        emit timechanged(time);
        return;
    }
    emit timechanged(time);
    update();
    //time--;
}



void draw::paintEvent(QPaintEvent *ev)
{
    if(error) return;
    if(!dirt){
    if(started){
    drawbackground(ev);
    }
    if(filed){



        drawtrace(ev,time);
        drawcircus(ev,time);
        drawwash(ev);
        drawblock(ev);
        if(wash.yes==false){
           // playsound(time);
        }


    }
    }
    else{//画污染次数
        if(started){
        drawbackground(ev);
        }
        if(filed){
            //drawwash(ev);
            drawdirt(ev,time);
        }
    }
}

void draw::mousePressEvent(QMouseEvent *ev)
{

    int x=ev->x();
    int y=ev->y();
    //qDebug()<<x<<" "<<y<<endl;
    pair<int,int>p((x-100)/50,(y-100)/50);
    if(mouseblock.count(p)==0){
        mouseblock.insert(p);
        update();
//        QPainter p(this);
//        p.setBrush(Qt::red);
//        p.drawRect((x-100)/50*50+100,(y-100)/50*50+100,50,50);
    }
    else{
        mouseblock.erase(p);
//        QPainter p(this);
//        p.setBrush(Qt::white);
//        p.drawRect((x-100)/50*50+100,(y-100)/50*50+100,50,50);
    }
}
