package edu.syr.hw6;

public abstract class Text {
    protected String text = "";
    public String getText() {
        return text;
    }

    @Override
    public abstract String toString();
    public abstract String toMarkdown();

    public static void main(String[] args) {
        Text[] pangram = new Text[11];
        pangram[0] = new Element("The");
        pangram[1] = new Italic(new Element("quick"));
        pangram[2] = new Bold( new Element("Bold"));
        pangram[3] = new Element("fox");
        pangram[4] = new Element("jumps");
        pangram[5] = new Element("over");
        pangram[6] = new Element("the");
        pangram[7] = new Strikethru(new Element("lazy"));
        pangram[8] = new Element("dog");
        pangram[9] = new Bold(new Italic(new Strikethru(new Element("comb-test"))));
        pangram[10] = new Italic(new Strikethru(new Bold(new Element("comb-test"))));

        StringBuffer justText = new StringBuffer();
        StringBuffer markdown = new StringBuffer();
        for (Text e: pangram) {
            justText.append(e.toString() + " ");
            markdown.append(e.toMarkdown()+ " ");
        }
        System.out.println(justText.toString());

        System.out.println(markdown.toString());
    }

}