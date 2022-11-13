void *downtime() {
    for(int i = 0; i < 3; i++){
    sleep(2);
    printf("Balancing\n");
    balanceTree(root);
    }
    return NULL;
}

void *ServeClient(char *client) {
    FILE* fp = fopen(client,"r");
    if(fp == NULL){
        printf("Cannot open file %s",client);
        exit(-1);
    }
    const unsigned maxlength = 256;
    char string[maxlength];
    while (!feof(fp)) {
        fgets(string,maxlength,fp);
        char function[20];
        int num;
        fscanf(fp,"%s %d",function, &num);
        pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;
        if(strcmp(function, "addNode") == 0){
            pthread_rwlock_wrlock(&lock);
            addNode(root,num);
            pthread_rwlock_unlock(&lock);
            printf("[%s]insertNode <%d>\n",client,num);
        }
        if(strcmp(function, "removeNode") == 0){
            pthread_rwlock_wrlock(&lock);
            removeNode(root,num);
            pthread_rwlock_unlock(&lock);
            printf("[%s]deleteNode <%d>\n",client,num);
        }
        if(strcmp(function, "countNodes") == 0){
            pthread_rwlock_rdlock(&lock);
            countNodes(root);
            pthread_rwlock_unlock(&lock);
            printf("[%s]countNodes = <%d>\n",client, countNodes(root));
        }
        if(strcmp(function, "avgSubtree") == 0){
            pthread_rwlock_rdlock(&lock);
            avgSubtree(root);
            pthread_rwlock_unlock(&lock);
            printf("[%s]avgSubtree =  <%f>\n",client, avgSubtree(root));
        }
    }
    fclose(fp);
    return NULL;
}
