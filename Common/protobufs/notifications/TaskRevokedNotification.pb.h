// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TaskRevokedNotification.proto

#ifndef PROTOBUF_TaskRevokedNotification_2eproto__INCLUDED
#define PROTOBUF_TaskRevokedNotification_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Notifications {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_TaskRevokedNotification_2eproto();
void protobuf_AssignDesc_TaskRevokedNotification_2eproto();
void protobuf_ShutdownFile_TaskRevokedNotification_2eproto();

class TaskRevokedNotification;

// ===================================================================

class TaskRevokedNotification : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification) */ {
 public:
  TaskRevokedNotification();
  virtual ~TaskRevokedNotification();

  TaskRevokedNotification(const TaskRevokedNotification& from);

  inline TaskRevokedNotification& operator=(const TaskRevokedNotification& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TaskRevokedNotification& default_instance();

  void Swap(TaskRevokedNotification* other);

  // implements Message ----------------------------------------------

  inline TaskRevokedNotification* New() const { return New(NULL); }

  TaskRevokedNotification* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TaskRevokedNotification& from);
  void MergeFrom(const TaskRevokedNotification& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(TaskRevokedNotification* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string class_name = 1 [default = "TaskRevokedNotification"];
  bool has_class_name() const;
  void clear_class_name();
  static const int kClassNameFieldNumber = 1;
  const ::std::string& class_name() const;
  void set_class_name(const ::std::string& value);
  void set_class_name(const char* value);
  void set_class_name(const char* value, size_t size);
  ::std::string* mutable_class_name();
  ::std::string* release_class_name();
  void set_allocated_class_name(::std::string* class_name);

  // required int32 task_id = 2;
  bool has_task_id() const;
  void clear_task_id();
  static const int kTaskIdFieldNumber = 2;
  ::google::protobuf::int32 task_id() const;
  void set_task_id(::google::protobuf::int32 value);

  // required int32 claimant_id = 3;
  bool has_claimant_id() const;
  void clear_claimant_id();
  static const int kClaimantIdFieldNumber = 3;
  ::google::protobuf::int32 claimant_id() const;
  void set_claimant_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification)
 private:
  inline void set_has_class_name();
  inline void clear_has_class_name();
  inline void set_has_task_id();
  inline void clear_has_task_id();
  inline void set_has_claimant_id();
  inline void clear_has_claimant_id();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  static ::std::string* _default_class_name_;
  ::google::protobuf::internal::ArenaStringPtr class_name_;
  ::google::protobuf::int32 task_id_;
  ::google::protobuf::int32 claimant_id_;
  friend void  protobuf_AddDesc_TaskRevokedNotification_2eproto();
  friend void protobuf_AssignDesc_TaskRevokedNotification_2eproto();
  friend void protobuf_ShutdownFile_TaskRevokedNotification_2eproto();

  void InitAsDefaultInstance();
  static TaskRevokedNotification* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// TaskRevokedNotification

// required string class_name = 1 [default = "TaskRevokedNotification"];
inline bool TaskRevokedNotification::has_class_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TaskRevokedNotification::set_has_class_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TaskRevokedNotification::clear_has_class_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TaskRevokedNotification::clear_class_name() {
  class_name_.ClearToDefaultNoArena(_default_class_name_);
  clear_has_class_name();
}
inline const ::std::string& TaskRevokedNotification::class_name() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.class_name)
  return class_name_.GetNoArena(_default_class_name_);
}
inline void TaskRevokedNotification::set_class_name(const ::std::string& value) {
  set_has_class_name();
  class_name_.SetNoArena(_default_class_name_, value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.class_name)
}
inline void TaskRevokedNotification::set_class_name(const char* value) {
  set_has_class_name();
  class_name_.SetNoArena(_default_class_name_, ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.class_name)
}
inline void TaskRevokedNotification::set_class_name(const char* value, size_t size) {
  set_has_class_name();
  class_name_.SetNoArena(_default_class_name_,
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.class_name)
}
inline ::std::string* TaskRevokedNotification::mutable_class_name() {
  set_has_class_name();
  // @@protoc_insertion_point(field_mutable:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.class_name)
  return class_name_.MutableNoArena(_default_class_name_);
}
inline ::std::string* TaskRevokedNotification::release_class_name() {
  // @@protoc_insertion_point(field_release:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.class_name)
  clear_has_class_name();
  return class_name_.ReleaseNoArena(_default_class_name_);
}
inline void TaskRevokedNotification::set_allocated_class_name(::std::string* class_name) {
  if (class_name != NULL) {
    set_has_class_name();
  } else {
    clear_has_class_name();
  }
  class_name_.SetAllocatedNoArena(_default_class_name_, class_name);
  // @@protoc_insertion_point(field_set_allocated:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.class_name)
}

// required int32 task_id = 2;
inline bool TaskRevokedNotification::has_task_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TaskRevokedNotification::set_has_task_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TaskRevokedNotification::clear_has_task_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TaskRevokedNotification::clear_task_id() {
  task_id_ = 0;
  clear_has_task_id();
}
inline ::google::protobuf::int32 TaskRevokedNotification::task_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.task_id)
  return task_id_;
}
inline void TaskRevokedNotification::set_task_id(::google::protobuf::int32 value) {
  set_has_task_id();
  task_id_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.task_id)
}

// required int32 claimant_id = 3;
inline bool TaskRevokedNotification::has_claimant_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TaskRevokedNotification::set_has_claimant_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TaskRevokedNotification::clear_has_claimant_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TaskRevokedNotification::clear_claimant_id() {
  claimant_id_ = 0;
  clear_has_claimant_id();
}
inline ::google::protobuf::int32 TaskRevokedNotification::claimant_id() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.claimant_id)
  return claimant_id_;
}
inline void TaskRevokedNotification::set_claimant_id(::google::protobuf::int32 value) {
  set_has_claimant_id();
  claimant_id_ = value;
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Notifications.TaskRevokedNotification.claimant_id)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Notifications
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_TaskRevokedNotification_2eproto__INCLUDED
