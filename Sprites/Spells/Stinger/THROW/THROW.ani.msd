Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"THROW"
    clock:100
Images:
    ?ImageList(str):
        "stinger.png"
Groups:
    @main
        ?content(int)<%s>{0}:
Animation:
    ?AnimationList(str):
        "PLAY_GROUP(main, -1)"