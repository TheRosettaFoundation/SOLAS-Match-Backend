// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: WorkflowNode.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_WorkflowNode_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_WorkflowNode_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Task.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_WorkflowNode_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_WorkflowNode_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_WorkflowNode_2eproto;
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {
class WorkflowNode;
class WorkflowNodeDefaultTypeInternal;
extern WorkflowNodeDefaultTypeInternal _WorkflowNode_default_instance_;
}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
PROTOBUF_NAMESPACE_OPEN
template<> ::SolasMatch::Common::Protobufs::Models::WorkflowNode* Arena::CreateMaybeMessage<::SolasMatch::Common::Protobufs::Models::WorkflowNode>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {

// ===================================================================

class WorkflowNode PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SolasMatch.Common.Protobufs.Models.WorkflowNode) */ {
 public:
  inline WorkflowNode() : WorkflowNode(nullptr) {};
  virtual ~WorkflowNode();

  WorkflowNode(const WorkflowNode& from);
  WorkflowNode(WorkflowNode&& from) noexcept
    : WorkflowNode() {
    *this = ::std::move(from);
  }

  inline WorkflowNode& operator=(const WorkflowNode& from) {
    CopyFrom(from);
    return *this;
  }
  inline WorkflowNode& operator=(WorkflowNode&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const WorkflowNode& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const WorkflowNode* internal_default_instance() {
    return reinterpret_cast<const WorkflowNode*>(
               &_WorkflowNode_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(WorkflowNode& a, WorkflowNode& b) {
    a.Swap(&b);
  }
  inline void Swap(WorkflowNode* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(WorkflowNode* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WorkflowNode* New() const final {
    return CreateMaybeMessage<WorkflowNode>(nullptr);
  }

  WorkflowNode* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WorkflowNode>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WorkflowNode& from);
  void MergeFrom(const WorkflowNode& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WorkflowNode* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SolasMatch.Common.Protobufs.Models.WorkflowNode";
  }
  protected:
  explicit WorkflowNode(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_WorkflowNode_2eproto);
    return ::descriptor_table_WorkflowNode_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNextFieldNumber = 3,
    kPreviousFieldNumber = 4,
    kTaskFieldNumber = 2,
    kTaskIdFieldNumber = 1,
  };
  // repeated int32 next = 3;
  int next_size() const;
  private:
  int _internal_next_size() const;
  public:
  void clear_next();
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_next(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      _internal_next() const;
  void _internal_add_next(::PROTOBUF_NAMESPACE_ID::int32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      _internal_mutable_next();
  public:
  ::PROTOBUF_NAMESPACE_ID::int32 next(int index) const;
  void set_next(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_next(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      next() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_next();

  // repeated int32 previous = 4;
  int previous_size() const;
  private:
  int _internal_previous_size() const;
  public:
  void clear_previous();
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_previous(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      _internal_previous() const;
  void _internal_add_previous(::PROTOBUF_NAMESPACE_ID::int32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      _internal_mutable_previous();
  public:
  ::PROTOBUF_NAMESPACE_ID::int32 previous(int index) const;
  void set_previous(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_previous(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      previous() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_previous();

  // optional .SolasMatch.Common.Protobufs.Models.Task task = 2;
  bool has_task() const;
  private:
  bool _internal_has_task() const;
  public:
  void clear_task();
  const ::SolasMatch::Common::Protobufs::Models::Task& task() const;
  ::SolasMatch::Common::Protobufs::Models::Task* release_task();
  ::SolasMatch::Common::Protobufs::Models::Task* mutable_task();
  void set_allocated_task(::SolasMatch::Common::Protobufs::Models::Task* task);
  private:
  const ::SolasMatch::Common::Protobufs::Models::Task& _internal_task() const;
  ::SolasMatch::Common::Protobufs::Models::Task* _internal_mutable_task();
  public:
  void unsafe_arena_set_allocated_task(
      ::SolasMatch::Common::Protobufs::Models::Task* task);
  ::SolasMatch::Common::Protobufs::Models::Task* unsafe_arena_release_task();

  // required int32 taskId = 1;
  bool has_taskid() const;
  private:
  bool _internal_has_taskid() const;
  public:
  void clear_taskid();
  ::PROTOBUF_NAMESPACE_ID::int32 taskid() const;
  void set_taskid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_taskid() const;
  void _internal_set_taskid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:SolasMatch.Common.Protobufs.Models.WorkflowNode)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > next_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > previous_;
  ::SolasMatch::Common::Protobufs::Models::Task* task_;
  ::PROTOBUF_NAMESPACE_ID::int32 taskid_;
  friend struct ::TableStruct_WorkflowNode_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// WorkflowNode

// required int32 taskId = 1;
inline bool WorkflowNode::_internal_has_taskid() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool WorkflowNode::has_taskid() const {
  return _internal_has_taskid();
}
inline void WorkflowNode::clear_taskid() {
  taskid_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkflowNode::_internal_taskid() const {
  return taskid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkflowNode::taskid() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Models.WorkflowNode.taskId)
  return _internal_taskid();
}
inline void WorkflowNode::_internal_set_taskid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  taskid_ = value;
}
inline void WorkflowNode::set_taskid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_taskid(value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Models.WorkflowNode.taskId)
}

// optional .SolasMatch.Common.Protobufs.Models.Task task = 2;
inline bool WorkflowNode::_internal_has_task() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || task_ != nullptr);
  return value;
}
inline bool WorkflowNode::has_task() const {
  return _internal_has_task();
}
inline const ::SolasMatch::Common::Protobufs::Models::Task& WorkflowNode::_internal_task() const {
  const ::SolasMatch::Common::Protobufs::Models::Task* p = task_;
  return p != nullptr ? *p : *reinterpret_cast<const ::SolasMatch::Common::Protobufs::Models::Task*>(
      &::SolasMatch::Common::Protobufs::Models::_Task_default_instance_);
}
inline const ::SolasMatch::Common::Protobufs::Models::Task& WorkflowNode::task() const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Models.WorkflowNode.task)
  return _internal_task();
}
inline void WorkflowNode::unsafe_arena_set_allocated_task(
    ::SolasMatch::Common::Protobufs::Models::Task* task) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(task_);
  }
  task_ = task;
  if (task) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SolasMatch.Common.Protobufs.Models.WorkflowNode.task)
}
inline ::SolasMatch::Common::Protobufs::Models::Task* WorkflowNode::release_task() {
  auto temp = unsafe_arena_release_task();
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::SolasMatch::Common::Protobufs::Models::Task* WorkflowNode::unsafe_arena_release_task() {
  // @@protoc_insertion_point(field_release:SolasMatch.Common.Protobufs.Models.WorkflowNode.task)
  _has_bits_[0] &= ~0x00000001u;
  ::SolasMatch::Common::Protobufs::Models::Task* temp = task_;
  task_ = nullptr;
  return temp;
}
inline ::SolasMatch::Common::Protobufs::Models::Task* WorkflowNode::_internal_mutable_task() {
  _has_bits_[0] |= 0x00000001u;
  if (task_ == nullptr) {
    auto* p = CreateMaybeMessage<::SolasMatch::Common::Protobufs::Models::Task>(GetArena());
    task_ = p;
  }
  return task_;
}
inline ::SolasMatch::Common::Protobufs::Models::Task* WorkflowNode::mutable_task() {
  // @@protoc_insertion_point(field_mutable:SolasMatch.Common.Protobufs.Models.WorkflowNode.task)
  return _internal_mutable_task();
}
inline void WorkflowNode::set_allocated_task(::SolasMatch::Common::Protobufs::Models::Task* task) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(task_);
  }
  if (task) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(task)->GetArena();
    if (message_arena != submessage_arena) {
      task = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, task, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  task_ = task;
  // @@protoc_insertion_point(field_set_allocated:SolasMatch.Common.Protobufs.Models.WorkflowNode.task)
}

// repeated int32 next = 3;
inline int WorkflowNode::_internal_next_size() const {
  return next_.size();
}
inline int WorkflowNode::next_size() const {
  return _internal_next_size();
}
inline void WorkflowNode::clear_next() {
  next_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkflowNode::_internal_next(int index) const {
  return next_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkflowNode::next(int index) const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Models.WorkflowNode.next)
  return _internal_next(index);
}
inline void WorkflowNode::set_next(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  next_.Set(index, value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Models.WorkflowNode.next)
}
inline void WorkflowNode::_internal_add_next(::PROTOBUF_NAMESPACE_ID::int32 value) {
  next_.Add(value);
}
inline void WorkflowNode::add_next(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_add_next(value);
  // @@protoc_insertion_point(field_add:SolasMatch.Common.Protobufs.Models.WorkflowNode.next)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
WorkflowNode::_internal_next() const {
  return next_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
WorkflowNode::next() const {
  // @@protoc_insertion_point(field_list:SolasMatch.Common.Protobufs.Models.WorkflowNode.next)
  return _internal_next();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
WorkflowNode::_internal_mutable_next() {
  return &next_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
WorkflowNode::mutable_next() {
  // @@protoc_insertion_point(field_mutable_list:SolasMatch.Common.Protobufs.Models.WorkflowNode.next)
  return _internal_mutable_next();
}

// repeated int32 previous = 4;
inline int WorkflowNode::_internal_previous_size() const {
  return previous_.size();
}
inline int WorkflowNode::previous_size() const {
  return _internal_previous_size();
}
inline void WorkflowNode::clear_previous() {
  previous_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkflowNode::_internal_previous(int index) const {
  return previous_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WorkflowNode::previous(int index) const {
  // @@protoc_insertion_point(field_get:SolasMatch.Common.Protobufs.Models.WorkflowNode.previous)
  return _internal_previous(index);
}
inline void WorkflowNode::set_previous(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  previous_.Set(index, value);
  // @@protoc_insertion_point(field_set:SolasMatch.Common.Protobufs.Models.WorkflowNode.previous)
}
inline void WorkflowNode::_internal_add_previous(::PROTOBUF_NAMESPACE_ID::int32 value) {
  previous_.Add(value);
}
inline void WorkflowNode::add_previous(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_add_previous(value);
  // @@protoc_insertion_point(field_add:SolasMatch.Common.Protobufs.Models.WorkflowNode.previous)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
WorkflowNode::_internal_previous() const {
  return previous_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
WorkflowNode::previous() const {
  // @@protoc_insertion_point(field_list:SolasMatch.Common.Protobufs.Models.WorkflowNode.previous)
  return _internal_previous();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
WorkflowNode::_internal_mutable_previous() {
  return &previous_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
WorkflowNode::mutable_previous() {
  // @@protoc_insertion_point(field_mutable_list:SolasMatch.Common.Protobufs.Models.WorkflowNode.previous)
  return _internal_mutable_previous();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_WorkflowNode_2eproto
