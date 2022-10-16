package syr.edu.hw6;

// public class Strikethru extends Dectorator {
public class Strikethru extends Element {
    public Strikethru(Element element) {
        super(element);
        markdown_val = "~~" + markdown_val + "~~";
        return;
    }

    public Strikethru(String val) {
        super(val);
        markdown_val = "~~" + markdown_val + "~~";
        return;
    } 
    // @Override
    // public String toMarkdown() {
    //     return "~~" + element.toMarkdown() + "~~";
    // }
}
