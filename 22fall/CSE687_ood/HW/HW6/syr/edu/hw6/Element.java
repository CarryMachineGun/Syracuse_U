package syr.edu.hw6;

public class Element {
    // private int type;
    protected String val;
    protected String markdown_val;

    public Element(){
        // type = 0;
        val = "";
        markdown_val = "";
    }

    public Element(String val){
        // type = 0;
        this.val = val;
        this.markdown_val = val;
    }

    public Element(Element element){
        this.val = element.val;
        this.markdown_val = element.markdown_val;
        return;
    }

    @Override
    public String toString(){
       return val + " "; 
    }

    public String toMarkdown(){
        return markdown_val + " ";
    }

    public static void main(String[] args) {
        Element[] pangram = new Element[9];
        pangram[0] = new Element("The");
        pangram[1] = new Italic("quick");
        pangram[2] = new Bold("bold");
        pangram[3] = new Element("fox");
        pangram[4] = new Element("jumps");
        pangram[5] = new Element("over");
        pangram[6] = new Element("the");
        pangram[7] = new Strikethru("lazy");
        // pangram[8] = new Element("dog");
        pangram[8] = new Strikethru(new Bold("dog"));
    
        StringBuffer justText = new StringBuffer();
        StringBuffer markdown = new StringBuffer();
        for (Element e: pangram) {
            justText.append(e.toString());
            markdown.append(e.toMarkdown());
        }
        System.out.println(justText.toString());
        // The quick bold fox jumps over the lazy dog
    
        System.out.println(markdown.toString());
        // The *quick* **bold** fox jumped over the ~~lazy~~ dog
    } 
}
