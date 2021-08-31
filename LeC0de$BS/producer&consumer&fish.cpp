//producer & consumer model
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
int maxLength = 5;
int num = 0;
stack<char> stack_;
void* producer(void *){
    //pthread_detach(pthread_self());
    while(true){
        pthread_mutex_lock(&mutex);
        while(!(num < maxLength))
            pthread_cond_wait(&cv,&mutex);
        stack_.push('(');
        system("cls");
        //print stack
        std::stack<char> stack__(stack_);
        while(!stack__.empty())
        {
            cout << stack__.top();
            stack__.pop();
        }
//        cout << endl;
//        usleep(100000);
//        msleep(1000);

        ++num;
        if(num == 1)
            pthread_cond_signal(&cv);
        pthread_mutex_unlock(&mutex);
    }
}

void* consumer(void *){
    //pthread_detach(pthread_self());
    while(true){
        pthread_mutex_lock(&mutex);
        while(!(num > 0))
            pthread_cond_wait(&cv,&mutex);
//        printf(")");
        stack_.pop();
        //print stack_
        std::stack<char> stack__(stack_);
        system("cls");
        while(!stack__.empty())
        {
            cout << stack__.top();
            stack__.pop();
        }
//        usleep(100000);
        --num;
        if(num == maxLength - 1)
            pthread_cond_signal(&cv);
        pthread_mutex_unlock(&mutex);
    }
}
//fish model
char cond = 'A';
void* leftBracket(void*){
    while(true){
        pthread_mutex_lock(&mutex);
        while(!(cond == 'A' || cond == 'C' || cond == 'E'))
            pthread_cond_wait(&cv,&mutex);
        switch(cond){
        case 'A':
            cond = 'B';
            pthread_cond_broadcast(&cv);
            break;
        case 'C':
            cond = 'D';
            pthread_cond_broadcast(&cv);
            break;
        case 'E':
            cond = 'F';
            pthread_cond_broadcast(&cv);
            break;
        }
        cout << '<';
        usleep(500000);
        pthread_mutex_unlock(&mutex);
    }
}
void* rightBracket(void*){
    while(true){
        pthread_mutex_lock(&mutex);
        while(!(cond == 'A' || cond == 'B' || cond == 'D'))
            pthread_cond_wait(&cv,&mutex);
        switch(cond){
        case 'A':
            cond = 'C';
            pthread_cond_broadcast(&cv);
            break;
        case 'B':
            cond = 'E';
            pthread_cond_broadcast(&cv);
            break;
        case 'D':
            cond = 'G';
            pthread_cond_broadcast(&cv);
            break;
        }
        cout << '>';
        usleep(500000);
        pthread_mutex_unlock(&mutex);
    }
}

void* underline(void*){
    while(true){
        pthread_mutex_lock(&mutex);
        while(!(cond == 'F' || cond == 'G'))
            pthread_cond_wait(&cv,&mutex);
        cond = 'A';
        pthread_cond_broadcast(&cv);
        cout << '\n';
        usleep(500000);
        pthread_mutex_unlock(&mutex);
    }
}


int main(){
    pthread_t left_th,right_th,underline_th;
    pthread_create(&left_th,NULL,leftBracket,NULL);
    pthread_create(&right_th,NULL,rightBracket,NULL);
    pthread_create(&underline_th,NULL,underline,NULL);
    pthread_join(left_th,NULL);
    pthread_join(right_th,NULL);
    pthread_join(underline_th,NULL);
    return 0;

}