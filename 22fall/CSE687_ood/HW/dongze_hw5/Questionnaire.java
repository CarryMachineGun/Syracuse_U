package edu.syr.hw5;


import java.io.PrintStream;
import java.util.*;

class Question {
    private String q;
    private String prompt;
    private List acceptableAnswers;
    public Question(String q, String prompt, List acceptable) {
        this.q = q;
        this.prompt = prompt;
        acceptableAnswers = acceptable;
    }
    public void render(PrintStream p) {
        p.println(q);
        p.println(prompt);
    }
    public boolean isAcceptableAnswer(String s) {
        return acceptableAnswers.contains(s);
    }
    public boolean isAcceptableAnswer(int a){
        return acceptableAnswers.contains(a);
    }
    public String getPrompt(){
        return this.prompt;
    }
}
public class Questionnaire {

    List<Question> questions;
    public Questionnaire() {
        questions = new ArrayList<>();
    }
    public void addQuestion(Question q) {
        questions.add(q);
    }
    public List<String> administerQuestionnaire() {
        List<String> answers = new ArrayList<>();
        Scanner sc = new Scanner(System.in);
        for (Question q: questions) {
            q.render(System.out);
            String response = "";
            if(q.getPrompt()=="Rate from 1 to 5: "){//Likert Scale Question
                int response2 = 0;
                do {
                    while(!sc.hasNextInt()){
                        System.out.println("must be int 1-5");
                        sc.next();
                    }
                    response2 = sc.nextInt();
                } while (!q.isAcceptableAnswer(response2));
                switch (response2){
                    case 1:
                        response = "Strongly Agree";
                        break;
                    case 2:
                        response = "Somewhat Agree";
                        break;
                    case 3:
                        response = "Neutral";
                        break;
                    case 4:
                        response = "Somewhat Disagree";
                        break;
                    case 5:
                        response = "Strong Disagree";
                        break;
                }
            }
            else {// normal question
                do {
                    response = sc.nextLine();
                } while (!q.isAcceptableAnswer(response));
            }
            answers.add(response);
        }
        return answers;
    }

    public static void main(String[] args) {
        Questionnaire q = new Questionnaire();
        q.addQuestion(new Question("Are you awake?", "True or False: ", Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("Have you had coffee?", "True or False: ", Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("Are you ready to get to work?", "True or False: ", Arrays.asList("True", "False", "true", "false", "t", "f", "T", "F")));
        q.addQuestion(new Question("CSE 687 is awesome","Rate from 1 to 5: ",Arrays.asList(1,2,3,4,5)));
        List<String> answers = q.administerQuestionnaire();

        System.out.println("complete!");
        System.out.println(answers);
    }
}
