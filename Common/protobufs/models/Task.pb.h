// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Task.proto

#ifndef PROTOBUF_Task_2eproto__INCLUDED
#define PROTOBUF_Task_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Task_2eproto();
void protobuf_AssignDesc_Task_2eproto();
void protobuf_ShutdownFile_Task_2eproto();

class Task;

// ===================================================================

class Task : public ::google::protobuf::Message {
 public:
  Task();
  virtual ~Task();
  
  Task(const Task& from);
  
  inline Task& operator=(const Task& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Task& default_instance();
  
  void Swap(Task* other);
  
  // implements Message ----------------------------------------------
  
  Task* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Task& from);
  void MergeFrom(const Task& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // optional int32 org_id = 2;
  inline bool has_org_id() const;
  inline void clear_org_id();
  static const int kOrgIdFieldNumber = 2;
  inline ::google::protobuf::int32 org_id() const;
  inline void set_org_id(::google::protobuf::int32 value);
  
  // optional string title = 3;
  inline bool has_title() const;
  inline void clear_title();
  static const int kTitleFieldNumber = 3;
  inline const ::std::string& title() const;
  inline void set_title(const ::std::string& value);
  inline void set_title(const char* value);
  inline void set_title(const char* value, size_t size);
  inline ::std::string* mutable_title();
  inline ::std::string* release_title();
  
  // optional string impact = 4;
  inline bool has_impact() const;
  inline void clear_impact();
  static const int kImpactFieldNumber = 4;
  inline const ::std::string& impact() const;
  inline void set_impact(const ::std::string& value);
  inline void set_impact(const char* value);
  inline void set_impact(const char* value, size_t size);
  inline ::std::string* mutable_impact();
  inline ::std::string* release_impact();
  
  // optional string reference_page = 5;
  inline bool has_reference_page() const;
  inline void clear_reference_page();
  static const int kReferencePageFieldNumber = 5;
  inline const ::std::string& reference_page() const;
  inline void set_reference_page(const ::std::string& value);
  inline void set_reference_page(const char* value);
  inline void set_reference_page(const char* value, size_t size);
  inline ::std::string* mutable_reference_page();
  inline ::std::string* release_reference_page();
  
  // optional int32 word_count = 6;
  inline bool has_word_count() const;
  inline void clear_word_count();
  static const int kWordCountFieldNumber = 6;
  inline ::google::protobuf::int32 word_count() const;
  inline void set_word_count(::google::protobuf::int32 value);
  
  // optional int32 source_lang_id = 7;
  inline bool has_source_lang_id() const;
  inline void clear_source_lang_id();
  static const int kSourceLangIdFieldNumber = 7;
  inline ::google::protobuf::int32 source_lang_id() const;
  inline void set_source_lang_id(::google::protobuf::int32 value);
  
  // optional int32 target_lang_id = 8;
  inline bool has_target_lang_id() const;
  inline void clear_target_lang_id();
  static const int kTargetLangIdFieldNumber = 8;
  inline ::google::protobuf::int32 target_lang_id() const;
  inline void set_target_lang_id(::google::protobuf::int32 value);
  
  // optional string created_time = 9;
  inline bool has_created_time() const;
  inline void clear_created_time();
  static const int kCreatedTimeFieldNumber = 9;
  inline const ::std::string& created_time() const;
  inline void set_created_time(const ::std::string& value);
  inline void set_created_time(const char* value);
  inline void set_created_time(const char* value, size_t size);
  inline ::std::string* mutable_created_time();
  inline ::std::string* release_created_time();
  
  // optional int32 source_region_id = 10;
  inline bool has_source_region_id() const;
  inline void clear_source_region_id();
  static const int kSourceRegionIdFieldNumber = 10;
  inline ::google::protobuf::int32 source_region_id() const;
  inline void set_source_region_id(::google::protobuf::int32 value);
  
  // optional int32 target_region_id = 11;
  inline bool has_target_region_id() const;
  inline void clear_target_region_id();
  static const int kTargetRegionIdFieldNumber = 11;
  inline ::google::protobuf::int32 target_region_id() const;
  inline void set_target_region_id(::google::protobuf::int32 value);
  
  // optional string status = 12;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 12;
  inline const ::std::string& status() const;
  inline void set_status(const ::std::string& value);
  inline void set_status(const char* value);
  inline void set_status(const char* value, size_t size);
  inline ::std::string* mutable_status();
  inline ::std::string* release_status();
  
  // repeated string tags = 13;
  inline int tags_size() const;
  inline void clear_tags();
  static const int kTagsFieldNumber = 13;
  inline const ::std::string& tags(int index) const;
  inline ::std::string* mutable_tags(int index);
  inline void set_tags(int index, const ::std::string& value);
  inline void set_tags(int index, const char* value);
  inline void set_tags(int index, const char* value, size_t size);
  inline ::std::string* add_tags();
  inline void add_tags(const ::std::string& value);
  inline void add_tags(const char* value);
  inline void add_tags(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& tags() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_tags();
  
  // required string deadline = 14;
  inline bool has_deadline() const;
  inline void clear_deadline();
  static const int kDeadlineFieldNumber = 14;
  inline const ::std::string& deadline() const;
  inline void set_deadline(const ::std::string& value);
  inline void set_deadline(const char* value);
  inline void set_deadline(const char* value, size_t size);
  inline ::std::string* mutable_deadline();
  inline ::std::string* release_deadline();
  
  // @@protoc_insertion_point(class_scope:Task)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_org_id();
  inline void clear_has_org_id();
  inline void set_has_title();
  inline void clear_has_title();
  inline void set_has_impact();
  inline void clear_has_impact();
  inline void set_has_reference_page();
  inline void clear_has_reference_page();
  inline void set_has_word_count();
  inline void clear_has_word_count();
  inline void set_has_source_lang_id();
  inline void clear_has_source_lang_id();
  inline void set_has_target_lang_id();
  inline void clear_has_target_lang_id();
  inline void set_has_created_time();
  inline void clear_has_created_time();
  inline void set_has_source_region_id();
  inline void clear_has_source_region_id();
  inline void set_has_target_region_id();
  inline void clear_has_target_region_id();
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_deadline();
  inline void clear_has_deadline();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 org_id_;
  ::std::string* title_;
  ::std::string* impact_;
  ::std::string* reference_page_;
  ::google::protobuf::int32 word_count_;
  ::google::protobuf::int32 source_lang_id_;
  ::std::string* created_time_;
  ::google::protobuf::int32 target_lang_id_;
  ::google::protobuf::int32 source_region_id_;
  ::std::string* status_;
  ::google::protobuf::RepeatedPtrField< ::std::string> tags_;
  ::std::string* deadline_;
  ::google::protobuf::int32 target_region_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(14 + 31) / 32];
  
  friend void  protobuf_AddDesc_Task_2eproto();
  friend void protobuf_AssignDesc_Task_2eproto();
  friend void protobuf_ShutdownFile_Task_2eproto();
  
  void InitAsDefaultInstance();
  static Task* default_instance_;
};
// ===================================================================


// ===================================================================

// Task

// required int32 id = 1;
inline bool Task::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Task::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Task::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Task::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 Task::id() const {
  return id_;
}
inline void Task::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// optional int32 org_id = 2;
inline bool Task::has_org_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Task::set_has_org_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Task::clear_has_org_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Task::clear_org_id() {
  org_id_ = 0;
  clear_has_org_id();
}
inline ::google::protobuf::int32 Task::org_id() const {
  return org_id_;
}
inline void Task::set_org_id(::google::protobuf::int32 value) {
  set_has_org_id();
  org_id_ = value;
}

// optional string title = 3;
inline bool Task::has_title() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Task::set_has_title() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Task::clear_has_title() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Task::clear_title() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    title_->clear();
  }
  clear_has_title();
}
inline const ::std::string& Task::title() const {
  return *title_;
}
inline void Task::set_title(const ::std::string& value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void Task::set_title(const char* value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void Task::set_title(const char* value, size_t size) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task::mutable_title() {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  return title_;
}
inline ::std::string* Task::release_title() {
  clear_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = title_;
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string impact = 4;
inline bool Task::has_impact() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Task::set_has_impact() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Task::clear_has_impact() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Task::clear_impact() {
  if (impact_ != &::google::protobuf::internal::kEmptyString) {
    impact_->clear();
  }
  clear_has_impact();
}
inline const ::std::string& Task::impact() const {
  return *impact_;
}
inline void Task::set_impact(const ::std::string& value) {
  set_has_impact();
  if (impact_ == &::google::protobuf::internal::kEmptyString) {
    impact_ = new ::std::string;
  }
  impact_->assign(value);
}
inline void Task::set_impact(const char* value) {
  set_has_impact();
  if (impact_ == &::google::protobuf::internal::kEmptyString) {
    impact_ = new ::std::string;
  }
  impact_->assign(value);
}
inline void Task::set_impact(const char* value, size_t size) {
  set_has_impact();
  if (impact_ == &::google::protobuf::internal::kEmptyString) {
    impact_ = new ::std::string;
  }
  impact_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task::mutable_impact() {
  set_has_impact();
  if (impact_ == &::google::protobuf::internal::kEmptyString) {
    impact_ = new ::std::string;
  }
  return impact_;
}
inline ::std::string* Task::release_impact() {
  clear_has_impact();
  if (impact_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = impact_;
    impact_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string reference_page = 5;
inline bool Task::has_reference_page() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Task::set_has_reference_page() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Task::clear_has_reference_page() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Task::clear_reference_page() {
  if (reference_page_ != &::google::protobuf::internal::kEmptyString) {
    reference_page_->clear();
  }
  clear_has_reference_page();
}
inline const ::std::string& Task::reference_page() const {
  return *reference_page_;
}
inline void Task::set_reference_page(const ::std::string& value) {
  set_has_reference_page();
  if (reference_page_ == &::google::protobuf::internal::kEmptyString) {
    reference_page_ = new ::std::string;
  }
  reference_page_->assign(value);
}
inline void Task::set_reference_page(const char* value) {
  set_has_reference_page();
  if (reference_page_ == &::google::protobuf::internal::kEmptyString) {
    reference_page_ = new ::std::string;
  }
  reference_page_->assign(value);
}
inline void Task::set_reference_page(const char* value, size_t size) {
  set_has_reference_page();
  if (reference_page_ == &::google::protobuf::internal::kEmptyString) {
    reference_page_ = new ::std::string;
  }
  reference_page_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task::mutable_reference_page() {
  set_has_reference_page();
  if (reference_page_ == &::google::protobuf::internal::kEmptyString) {
    reference_page_ = new ::std::string;
  }
  return reference_page_;
}
inline ::std::string* Task::release_reference_page() {
  clear_has_reference_page();
  if (reference_page_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = reference_page_;
    reference_page_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional int32 word_count = 6;
inline bool Task::has_word_count() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Task::set_has_word_count() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Task::clear_has_word_count() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Task::clear_word_count() {
  word_count_ = 0;
  clear_has_word_count();
}
inline ::google::protobuf::int32 Task::word_count() const {
  return word_count_;
}
inline void Task::set_word_count(::google::protobuf::int32 value) {
  set_has_word_count();
  word_count_ = value;
}

// optional int32 source_lang_id = 7;
inline bool Task::has_source_lang_id() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Task::set_has_source_lang_id() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Task::clear_has_source_lang_id() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Task::clear_source_lang_id() {
  source_lang_id_ = 0;
  clear_has_source_lang_id();
}
inline ::google::protobuf::int32 Task::source_lang_id() const {
  return source_lang_id_;
}
inline void Task::set_source_lang_id(::google::protobuf::int32 value) {
  set_has_source_lang_id();
  source_lang_id_ = value;
}

// optional int32 target_lang_id = 8;
inline bool Task::has_target_lang_id() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Task::set_has_target_lang_id() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Task::clear_has_target_lang_id() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Task::clear_target_lang_id() {
  target_lang_id_ = 0;
  clear_has_target_lang_id();
}
inline ::google::protobuf::int32 Task::target_lang_id() const {
  return target_lang_id_;
}
inline void Task::set_target_lang_id(::google::protobuf::int32 value) {
  set_has_target_lang_id();
  target_lang_id_ = value;
}

// optional string created_time = 9;
inline bool Task::has_created_time() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Task::set_has_created_time() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Task::clear_has_created_time() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Task::clear_created_time() {
  if (created_time_ != &::google::protobuf::internal::kEmptyString) {
    created_time_->clear();
  }
  clear_has_created_time();
}
inline const ::std::string& Task::created_time() const {
  return *created_time_;
}
inline void Task::set_created_time(const ::std::string& value) {
  set_has_created_time();
  if (created_time_ == &::google::protobuf::internal::kEmptyString) {
    created_time_ = new ::std::string;
  }
  created_time_->assign(value);
}
inline void Task::set_created_time(const char* value) {
  set_has_created_time();
  if (created_time_ == &::google::protobuf::internal::kEmptyString) {
    created_time_ = new ::std::string;
  }
  created_time_->assign(value);
}
inline void Task::set_created_time(const char* value, size_t size) {
  set_has_created_time();
  if (created_time_ == &::google::protobuf::internal::kEmptyString) {
    created_time_ = new ::std::string;
  }
  created_time_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task::mutable_created_time() {
  set_has_created_time();
  if (created_time_ == &::google::protobuf::internal::kEmptyString) {
    created_time_ = new ::std::string;
  }
  return created_time_;
}
inline ::std::string* Task::release_created_time() {
  clear_has_created_time();
  if (created_time_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = created_time_;
    created_time_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional int32 source_region_id = 10;
inline bool Task::has_source_region_id() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Task::set_has_source_region_id() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Task::clear_has_source_region_id() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Task::clear_source_region_id() {
  source_region_id_ = 0;
  clear_has_source_region_id();
}
inline ::google::protobuf::int32 Task::source_region_id() const {
  return source_region_id_;
}
inline void Task::set_source_region_id(::google::protobuf::int32 value) {
  set_has_source_region_id();
  source_region_id_ = value;
}

// optional int32 target_region_id = 11;
inline bool Task::has_target_region_id() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Task::set_has_target_region_id() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Task::clear_has_target_region_id() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Task::clear_target_region_id() {
  target_region_id_ = 0;
  clear_has_target_region_id();
}
inline ::google::protobuf::int32 Task::target_region_id() const {
  return target_region_id_;
}
inline void Task::set_target_region_id(::google::protobuf::int32 value) {
  set_has_target_region_id();
  target_region_id_ = value;
}

// optional string status = 12;
inline bool Task::has_status() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Task::set_has_status() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Task::clear_has_status() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Task::clear_status() {
  if (status_ != &::google::protobuf::internal::kEmptyString) {
    status_->clear();
  }
  clear_has_status();
}
inline const ::std::string& Task::status() const {
  return *status_;
}
inline void Task::set_status(const ::std::string& value) {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  status_->assign(value);
}
inline void Task::set_status(const char* value) {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  status_->assign(value);
}
inline void Task::set_status(const char* value, size_t size) {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  status_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task::mutable_status() {
  set_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    status_ = new ::std::string;
  }
  return status_;
}
inline ::std::string* Task::release_status() {
  clear_has_status();
  if (status_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = status_;
    status_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// repeated string tags = 13;
inline int Task::tags_size() const {
  return tags_.size();
}
inline void Task::clear_tags() {
  tags_.Clear();
}
inline const ::std::string& Task::tags(int index) const {
  return tags_.Get(index);
}
inline ::std::string* Task::mutable_tags(int index) {
  return tags_.Mutable(index);
}
inline void Task::set_tags(int index, const ::std::string& value) {
  tags_.Mutable(index)->assign(value);
}
inline void Task::set_tags(int index, const char* value) {
  tags_.Mutable(index)->assign(value);
}
inline void Task::set_tags(int index, const char* value, size_t size) {
  tags_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task::add_tags() {
  return tags_.Add();
}
inline void Task::add_tags(const ::std::string& value) {
  tags_.Add()->assign(value);
}
inline void Task::add_tags(const char* value) {
  tags_.Add()->assign(value);
}
inline void Task::add_tags(const char* value, size_t size) {
  tags_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Task::tags() const {
  return tags_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Task::mutable_tags() {
  return &tags_;
}

// required string deadline = 14;
inline bool Task::has_deadline() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void Task::set_has_deadline() {
  _has_bits_[0] |= 0x00002000u;
}
inline void Task::clear_has_deadline() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void Task::clear_deadline() {
  if (deadline_ != &::google::protobuf::internal::kEmptyString) {
    deadline_->clear();
  }
  clear_has_deadline();
}
inline const ::std::string& Task::deadline() const {
  return *deadline_;
}
inline void Task::set_deadline(const ::std::string& value) {
  set_has_deadline();
  if (deadline_ == &::google::protobuf::internal::kEmptyString) {
    deadline_ = new ::std::string;
  }
  deadline_->assign(value);
}
inline void Task::set_deadline(const char* value) {
  set_has_deadline();
  if (deadline_ == &::google::protobuf::internal::kEmptyString) {
    deadline_ = new ::std::string;
  }
  deadline_->assign(value);
}
inline void Task::set_deadline(const char* value, size_t size) {
  set_has_deadline();
  if (deadline_ == &::google::protobuf::internal::kEmptyString) {
    deadline_ = new ::std::string;
  }
  deadline_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task::mutable_deadline() {
  set_has_deadline();
  if (deadline_ == &::google::protobuf::internal::kEmptyString) {
    deadline_ = new ::std::string;
  }
  return deadline_;
}
inline ::std::string* Task::release_deadline() {
  clear_has_deadline();
  if (deadline_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = deadline_;
    deadline_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Task_2eproto__INCLUDED
