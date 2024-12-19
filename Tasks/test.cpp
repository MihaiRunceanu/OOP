#include "test.h"

void Tests::test_domain(){
    vector<string> v;
    v.push_back("Matei");
    v.push_back("Robert");
    v.push_back("Razvan");
    auto task = Task(1,"ABCD", v, "open");
    assert(task.getId()==1);
    assert(task.getDescription()=="ABCD");
    assert(task.getProgrammers()==v);
    assert(task.getStatus()=="open");
    task.setStatus("inprogress");
    assert(task.getStatus()=="inprogress");
}

void Tests::test_repo(){
    Repository repo("C:\\Scoala\\POO\\practic-Tasks\\Tasks\\test.txt");
    assert(repo.getAll().size()==5);
    assert(repo.findTask(1)==true);
    assert(repo.findTask(7)==false);
    vector<string> v;
    v.push_back("Matei");
    v.push_back("Robert");
    v.push_back("Razvan");
    auto elem = Task(7,"ABCD",v,"closed");
    repo.addTask(elem);
    assert(repo.findTask(7)==true);
    assert(repo.getAll().back().getStatus()=="closed");
    repo.setTaskStatus(7,"open");
    assert(repo.getAll().back().getStatus()=="open");
    repo.test_delete();
    assert(repo.getAll().size()==5);
}

void Tests::test_service(){
    Repository repo("C:\\Scoala\\POO\\practic-Tasks\\Tasks\\test.txt");
    Service serv(repo);
    assert(serv.getLen()==5);
    assert(serv.getAll().size()==5);
    string name;
    try{
        serv.searchByProgrammer(name);
        assert(false);
    }
    catch(runtime_error &e){
        assert(true);
    }
    try{
        vector<string> v;
        string nume, status;
        serv.addTask(1,nume,v,status);
        assert(false);
    }
    catch(runtime_error &e){
        assert(true);
    }
    try{
        vector<string> v;
        v.push_back("Mihai");
        serv.addTask(100,"Proiect",v,"ceva");
        assert(false);
    }
    catch(runtime_error &e){
        assert(true);
    }
    try{
        vector<string> v;
        v.push_back("Mihai");
        serv.addTask(1,"Proiect",v,"open");
        assert(false);
    }
    catch(runtime_error &e){
        assert(true);
    }
    vector<string> v;
    v.push_back("Mihai");
    serv.addTask(10,"Proiect",v,"open");
    serv.setTaskStatus(10,"inprogress");
    assert(serv.getLen()==6);
    serv.test_delete();
    auto rez=serv.getTasksByStatus("open");
    assert(rez.size()==2);
    rez=serv.getTasksByStatus("inprogress");
    assert(rez.size()==2);
    rez=serv.getTasksByStatus("closed");
    assert(rez.size()==1);
    rez=serv.getTasksByStatus("ceva");
    assert(rez.empty());
}

void Tests::test_all(){
    test_domain();
    test_repo();
    test_service();
}
