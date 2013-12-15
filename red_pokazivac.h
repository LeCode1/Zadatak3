struct telement{
	int ai,bi,ci,di,ei;
    string ime,prezime;
    short dan,mj,god;
    char spol;
};

struct qu{
    telement pacijent;
    qu *sljedeci;
};

struct que{
    qu *front,*rear;
};

que *InitQ(que *r){
    r = new que;
    qu *novi = new qu;
    novi->sljedeci = NULL;
    r->front = novi;
    r->rear = novi;
    return r;
}

bool IsEmptyQ(que *r){
    return r->rear == r->front;
    }
  
telement FrontQ(que *r){
    if(IsEmptyQ(r)) cout << "Red je prazan!" << endl;
    else return r->front->sljedeci->pacijent;
}
    
void EnQueueQ(telement p, que *r){
    qu *novi = new qu;
    novi->pacijent = p;
    novi->sljedeci = NULL;
    r->rear->sljedeci = novi;
    r->rear = novi;
}
    
void DeQueueQ(que *r){
    qu *brisi = r->front;
    r->front = r->front->sljedeci;
    delete brisi;
}
