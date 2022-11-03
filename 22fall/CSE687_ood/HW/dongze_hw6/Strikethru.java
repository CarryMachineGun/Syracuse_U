package edu.syr.hw6;

public class Strikethru extends TextDecorator {
    Text txt;

    public Strikethru(Text t) {
        txt = t;
    }

    public String getText(){
        return txt.getText();
    }

    @Override
    public String toString() {
        return txt.toString();
    }

    public String toMarkdown(){
        if(txt.toMarkdown().contains("~~")) return txt.toMarkdown(); //already strike
        return "~~" + txt.toMarkdown() + "~~";
    }
}
