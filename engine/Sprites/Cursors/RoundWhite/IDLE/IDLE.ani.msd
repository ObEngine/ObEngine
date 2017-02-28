Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"IDLE"
    clock:100
Images:
    ImageList:[0]
    model:"%s.png"
Groups:
    @main
        content:[0]
Animation:
    AnimationCode:[
        "PLAY_GROUP(main, -1)"
    ]