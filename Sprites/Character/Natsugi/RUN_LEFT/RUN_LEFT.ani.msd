Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"RUN_LEFT"
    clock:70
Images:
    ?ImageList(str)<"00%s.png">{51-56}:
Groups:
    @main
        ?content(int)<%s>{0-5}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, -1)"