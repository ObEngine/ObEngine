Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"IDLE"
    clock:100
Images:
    ?ImageList(str)<"%s.png">{0}:
Groups:
    @main
        ?content(int)<%s>{0}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, -1)"