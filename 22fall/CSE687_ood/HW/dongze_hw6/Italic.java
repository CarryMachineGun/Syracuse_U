package edu.syr.hw6;

public class Italic extends TextDecorator {
    Text txt;

    public Italic(Text t) {
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
        if(txt.toMarkdown().contains("_")) return txt.toMarkdown();// already italic
        else if(txt.toMarkdown().contains("**") && txt.toMarkdown().contains("~~")){ //already bold and strike
            String origin = txt.toMarkdown().substring(4,txt.toMarkdown().length()-4);
            return "~~**_" + origin + "_**~~";
        } else if(txt.toMarkdown().contains("**")){//already bold
            String origin = txt.toMarkdown().substring(2,txt.toMarkdown().length()-2);
            return "**_" + origin + "_**";
        } else if(txt.toMarkdown().contains("~~")){//already strike
            String origin = txt.toMarkdown().substring(2,txt.toMarkdown().length()-2);
            return "~~_" + origin + "_~~";
        }
        return "_" + txt.toMarkdown() + "_";
    }
}
