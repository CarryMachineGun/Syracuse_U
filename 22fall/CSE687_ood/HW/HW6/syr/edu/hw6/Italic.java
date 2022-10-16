package syr.edu.hw6;

// public class Italic extends Dectorator {
public class Italic extends Element {
    public Italic(Element element) {
        super(element);
        markdown_val = "*" + markdown_val + "*";
        return;
    }

    public Italic(String val) {
        super(val);
        markdown_val = "*" + markdown_val + "*";
        return;
    } 
    // @Override
    // public String toMarkdown() {
    //     return "*" + element.toMarkdown() + "*";
    // }
}
