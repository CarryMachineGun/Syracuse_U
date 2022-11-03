package edu.syr.hw6;

public class Element extends Text{
    public Element(String s){
        text = s;
    }

    @Override
    public String toString(){
        return getText();
    }

    public String toMarkdown() {
        return getText();
    }


}
