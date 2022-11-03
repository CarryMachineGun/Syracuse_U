package edu.syr.hw6;

public class Bold extends TextDecorator {
    Text txt;

    public Bold(Text t) {
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
        if(txt.toMarkdown().contains("**")) return txt.toMarkdown();
        else if(txt.toMarkdown().contains("~~")){//already strike
            String origin = txt.toMarkdown().substring(2,txt.toMarkdown().length()-2);
            return "~~**" + origin + "**~~";
        }
        return "**" + txt.toMarkdown() + "**";
    }
}
