Define Flag (VisualNovel);
Define Flag (Lock);

Meta:
    name:"dialogueRestaurant"
    ?allActors(str)<"%s,%s">{0,1}:
    
Dialogue:
    {@}action
        type:"action"
    {@}choice
        type:"choice"
    @0:action
        ?actionList(str):
            "setposition $0 300 300"
            "setposition $1 500 300"
            "setvisible $0"
            "setvisible $1"
            "setbehavior $0 neutral"
            "setbehavior $1 neutral"
            "say $0 Salut"
            "start @1"
    @1:choice
        question:"Tu connais la blague du con qui dit non ?"
        askerId:0
        @choices
            @0
                answer:"Oui"
                action:"@2"
            @1
                answer:"Non"
                action:"@3"
    @2:action
        ?actionList(str):
            "setbehavior $0 sad"
            "say $0 T'es pas drôle..."
            "say $1 Je t'ai bien eu !"
    @3:action
        ?actionList(str):
            "setbehavior $0 happy"
            "say $0 Haha t'es bon !"
            "setbehavior $1 sad"
            "say $1 Oh non je me suis fait avoir :("