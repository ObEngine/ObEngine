Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"THROW"
    clock:100
Images:
    ?ImageList(str)<"fire%s.png">{1}:
Groups:
    @main
        ?content(int)<%s>{0}:
Animation:
    ?AnimationList(str):
        "PLAY_GROUP(main, -1)"