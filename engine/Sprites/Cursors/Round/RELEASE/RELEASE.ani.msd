Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"RELEASE"
    clock:10
    play-mode:"FORCE"
Images:
    ?ImageList(string)<"%s.png">{1-9}:
Groups:
    @main
        ?content(int)<%s>{0-8}:
Animation:
    ?AnimationCode(string):
        "PLAY_GROUP(main, 1)"
        "CALL('IDLE')"