package syr.edu.hw6;

// public class Bold extends Dectorator {
public class Bold extends Element {
    public Bold(Element element) {
        super(element);
        markdown_val = "**" + markdown_val + "**";
        return;
    }

    public Bold(String val) {
        super(val);
        markdown_val = "**" + markdown_val + "**";
        return;
    }

    // @Override
    // public String toMarkdown() {
    // // return "**" + element.toMarkdown() + "**";
    // return markdown_val;
    // }
}
