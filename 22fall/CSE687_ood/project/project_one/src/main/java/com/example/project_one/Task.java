package com.example.project_one;

import java.sql.Timestamp;
import java.util.*;

import javax.persistence.ElementCollection;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

import ch.qos.logback.core.joran.conditional.ElseAction;

@Entity // This tells Hibernate to make a table out of this class
public class Task {
  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private Integer id;

  private Timestamp timestamp;

  // @ElementCollection
  // private List<String> user = new ArrayList<>();
  private String user;

  private String state;

  private String description;

  @ElementCollection
  private List<String> comments = new ArrayList<>();

  Task() {
    // timestamp = ;
    // user = b.user;
    // state = b.state;
    // description = b.description;
    // comments = new ArrayList<>(b.comments);
  }

  Task(Task b) {
    id = b.id;
    timestamp = b.timestamp;
    user = b.user;
    state = b.state;
    description = b.description;
    comments = new ArrayList<>(b.comments);
  }

  public Integer getId() {
    return id;
  }

  public void setId(Integer id) {
    this.id = id;
  }

  public String getTimestamp() {
    return timestamp.toString();
  }

  public void setTimestamp(Timestamp timestamp) {
    this.timestamp = timestamp;
  }

  public boolean setUser(String user) {
    if (user == null)
      return true;

    if (!user.equals("John") && !user.equals("Paul") && !user.equals("George") && !user.equals("Ringo"))
      return false;

    this.user = user;

    return true;
  }

  public String getUser() {
    return user;
  }

  public boolean setState(String state) {
    if (state == null)
      return true;

    if (state.equals("Todo"))
      this.state = state;
    else if (state.equals("Doing"))
      this.state = state;
    else if (state.equals("Done"))
      this.state = state;
    else
      return false;

    return true;
  }

  public String getState() {
    return state;
  }

  public void editDescription(String Description) {
    this.description = Description;
  }

  public String getDescription() {
    return description;
  }

  public void addComment(String new_comment) {
    comments.add(new_comment);
  }

  public List<String> getComment() {
    return comments;
  }
}
