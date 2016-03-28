Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"THROW"
    clock:0
Images:
    ?ImageList(str)<"%s.png">{1-5}:
Groups:
    @start
        clock:40
        ?content(int)<%s>{0-3}:
    @main
        clock:100
        ?content(int)<%s>{4}:
Animation:
    ?AnimationList(str):
        "PLAY_GROUP(start, 1)"
        "PLAY_GROUP(main, -1)"