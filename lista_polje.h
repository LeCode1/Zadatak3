struct telement{
	  int ai,bi,ci,di,ei;
    string ime,prezime;
    short dan,mj,god;
    char spol;
};

struct que{
    telement pacijent[10000];
    int front,rear;
};

int AddOne(int n){
    return (n+1)%10000;
}

que *InitQ(que *R){
    R = new que;
    R->front = 0;
    R->rear = 9999;
    return R;
}

bool IsEmptyQ(que *R){
    if(AddOne(R->rear) == R->front) return true;
    else return false;
}
    
telement FrontQ(que *R){
    return R->pacijent[R->front];
}

void EnQueueQ(telement p, que *R){
    int n;
    if(R->rear == 9999) n=0;
    else n = R->rear+1;
    R->pacijent[n] = p;
    R->rear = n;
}

void DeQueueQ(que *R){
    if(IsEmptyQ(R)) cout << "Red je prazan!" << endl;
    else{
        if(R->front==9999) R->front=0;
        else R->front++;
    }
}
